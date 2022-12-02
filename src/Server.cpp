/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 20:05:51 by estoffel          #+#    #+#             */
/*   Updated: 2022/12/02 16:46:08 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

#include "command.h"
#include "ft_irc.h"

#include <arpa/inet.h>

#include <cerrno>
#include <cstring>

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <sstream>

Server::Server() :
	startDate(Server::__getStartDate()),
	commandMap(*this),
	logger(DEBUG)
 {}

Server::~Server() {}

const int	&Server::getsocketfd() const {return this->_socketfd;}

const std::vector<pollfd>	&Server::getclientfd() const {return this->_clientfd;}

void	Server::__poll() {

	PollFdList::iterator it;
	int poll_ret;
	pollfd fd_serv;

	fd_serv.fd = _socketfd;
	fd_serv.events = POLLIN;

	_clientfd.push_back(fd_serv);

	while (KEEP_RUNNING)
	{
		poll_ret = poll(&*_clientfd.begin(), _clientfd.size(), -1);
		if (poll_ret == -1)
		{
			if (errno == EINTR)
				break;
			throw IOException("poll", errno); // TODO: gerer les signaux
		}

		for (it = _clientfd.begin(); KEEP_RUNNING && it != _clientfd.end();)
		{
			if (it->revents & POLLERR)
			{
				int errnum;
				socklen_t errnum_len;

				errnum_len = sizeof (errnum);
				getsockopt(it->fd, SOL_SOCKET, SO_ERROR, &errnum, &errnum_len);
				this->logger.log(ERROR, std::string("Error on socket ") + it->fd + ": " + std::strerror(errnum));

				ClientManager::iterator clientIt = this->clientManager.getClient(it->fd);

				if (clientIt != this->clientManager.end())
				{
					this->nickManager.unregisterNickname(clientIt->second.nickname);
					this->clientManager.removeClient(clientIt);
				}

				this->_clientfd.erase(it);
				continue;
			}
			else if (it->revents & POLLIN)
			{
				if (it->fd == _socketfd)
					this->__acceptClient();
				else if (__readFromClient(it->fd))
				{
					ClientManager::iterator clientIt = this->clientManager.getClient(it->fd);

					if (clientIt != this->clientManager.end())
					{
						this->nickManager.unregisterNickname(clientIt->second.nickname);
						this->clientManager.removeClient(clientIt);
					}

					this->_clientfd.erase(it);
					continue;
				}
			} else if (it->revents & POLLOUT)
				__writeToClient(it->fd);
			++it;
		}
		this->_clientfd.insert(this->_clientfd.end(), this->_newConnections.begin(), this->_newConnections.end());
		this->_newConnections.clear();
	}
	this->__shutdown();
}

void	Server::__socket(int port) {

	int	val = 1;
	_socketfd = socket(AF_INET, SOCK_STREAM, 0);
	if (_socketfd == -1)
		throw IOException("socket", errno);
	this->logger.log(DEBUG, "Socket created");
	if (setsockopt(_socketfd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof val))
		throw IOException("used_address", errno);

	sockaddr_in	serv_addr;
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);

	if (bind(_socketfd, (sockaddr*)&serv_addr, sizeof(serv_addr)) != 0)
		throw IOException("bind", errno);
	this->logger.log(DEBUG, "Socket bound");
	if (listen(_socketfd, SOMAXCONN) != 0)
		throw IOException("listen", errno);
	this->logger.log(INFO, std::string("Listening on port ") + port);
	Server::__poll();
}

Server::ChannelList::iterator Server::getChannel(std::string const& channelName)
{
	ChannelList::iterator it;

	for (it = this->channels.begin(); it != this->channels.end(); ++it)
		if (it->name == channelName)
			break;
	return it;
}

void Server::initCommands()
{
	this->logger.log(DEBUG, "Registering commands");
	this->commandMap.put("CAP", NULL);
	this->commandMap.put("PASS", cmd_pass);
	this->commandMap.put("USER", cmd_user);
	this->commandMap.put("NICK", cmd_nick);
	this->commandMap.put("QUIT", cmd_quit, CLIENT_STATE_LOGGED);
	this->commandMap.put("MOTD", cmd_motd, CLIENT_STATE_LOGGED);
	this->commandMap.put("OPER", cmd_oper, CLIENT_STATE_LOGGED);
	this->commandMap.put("JOIN", cmd_join, CLIENT_STATE_LOGGED);
	this->commandMap.put("PART", cmd_part, CLIENT_STATE_LOGGED);
	this->commandMap.put("DIE", cmd_die, CLIENT_STATE_LOGGED);
	this->commandMap.put("KILL", cmd_kill, CLIENT_STATE_LOGGED);
	this->commandMap.put("NOTICE", cmd_msg_common, CLIENT_STATE_LOGGED);
	this->commandMap.put("PRIVMSG", cmd_msg_common, CLIENT_STATE_LOGGED);
	this->commandMap.put("PING", cmd_ping);
	this->commandMap.put("PONG", cmd_pong);
}

void Server::loadOperatorFile(std::string const& file)
{
	std::ifstream in;
	std::string line;
	std::stringstream ss;
	OperatorEntry entry;

	in.open(file.c_str());
	if (in)
	{
		this->logger.log(DEBUG, "Registering operators");
		while (std::getline(in, line))
		{
			ss << line;
			ss >> entry.name >> entry.host >> entry.password;
			ss.clear();
			this->operatorPasswords.push_back(entry);
			this->logger.log(DEBUG, "+ " + entry.name + "@" + entry.host);
		}
	}
	else
	{
		this->logger.log(WARNING, "Failed to load operator file '" + file + "'");
		this->logger.log(WARNING, "There will be no operator for this server!");
	}
}

Recipient* Server::getRecipient(std::string const& identifier)
{
	if (identifier.empty())
		return NULL;
	if (identifier[0] == '#')
	{
		ChannelList::iterator it = this->getChannel(identifier);

		if (it != this->channels.end())
			return &*it;
	}
	else
	{
		ClientManager::iterator it = this->clientManager.getClient(identifier);

		if (it != this->clientManager.end())
			return &it->second;
	}
	return NULL;
}

void Server::__acceptClient()
{
	int fd;
	int errnum;
	sockaddr_in address;
	socklen_t addressLength;

	addressLength = sizeof (address);
	fd = ::accept(this->_socketfd, (sockaddr*)&address, &addressLength);

	if (fd == -1)
	{
		errnum = errno;
		this->logger.log(ERROR, std::string("Failed to accept client: ") + ::strerror(errnum));
		return;
	}
	this->logger.log(DEBUG, "<" + address + "> Accepted client");

	this->clientManager.addClient(Client(this, fd, address));

	pollfd newPollFd;

	newPollFd.fd = fd;
	newPollFd.events = POLLIN | POLLOUT;

	this->_newConnections.push_back(newPollFd);
}

bool Server::__readFromClient(int fd)
{
	ClientManager::iterator it = this->clientManager.getClient(fd);

	if (it != this->clientManager.end())
		return it->second.readFrom();
	this->logger.log(ERROR, std::string("No such client for socket file descriptor ") + fd);
	return false;
}

void Server::__writeToClient(int fd)
{
	ClientManager::iterator it = this->clientManager.getClient(fd);

	if (it != this->clientManager.end())
		it->second.writeTo();
	else
	{
		// TODO log error, client not found
	}
}

std::string Server::__getStartDate()
{
	char buffer[20];
	time_t timestamp;
	tm* timeinfo;
	size_t res;

	time(&timestamp);
	timeinfo = localtime(&timestamp);
	res = strftime(buffer, sizeof (buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
	return std::string(buffer, res);
}

void Server::__shutdown()
{
	ClientManager::iterator it;

	this->logger.log(INFO, "Shutting down...");
	for (it = this->clientManager.begin(); it != this->clientManager.end(); ++it)
		it->second.closeConnection();
}

std::ostream& operator<<(std::ostream& os, sockaddr_in& address)
{
	os << inet_ntoa(address.sin_addr);
	return os;
}

std::string operator+(std::string const& str, sockaddr_in& addr)
{
	std::stringstream ss;

	ss << str << addr;
	return ss.str();
}

std::string operator+(sockaddr_in& addr, std::string const& str)
{
	std::stringstream ss;

	ss << addr << str;
	return ss.str();
}

std::string operator+(std::string const& str, int n)
{
	std::stringstream ss;

	ss << str << n;
	return ss.str();
}
