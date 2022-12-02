/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 20:05:51 by estoffel          #+#    #+#             */
/*   Updated: 2022/12/01 02:00:15 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "ft_irc.h"
#include <algorithm>
#include <cerrno>
#include <fstream>
#include <iomanip>
#include <sstream>

Server::Server() :
	startDate(Server::__getStartDate()),
	commands(*this),
	clients(),
	logger(DEBUG)
 {}

Server::~Server() {}

Server::IoException::IoException(std::string const& syscall, int err):
	_what(syscall + ": " + std::strerror(err)) {}

Server::IoException::~IoException() throw() {}

const int	&Server::getsocketfd() const {return this->_socketfd;}

const std::vector<pollfd>	&Server::getclientfd() const {return this->_clientfd;}

const char*	Server::IoException::what() const throw() {

	return this->_what.c_str();
}

void	Server::__poll() {

	PollFdList::iterator it;
	ClientList::iterator clientIt;
	int errnum;
	socklen_t errnum_len;
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
			throw Server::IoException("poll", errno); // TODO: gerer les signaux
		}

		for (it = _clientfd.begin(); KEEP_RUNNING && it != _clientfd.end();)
		{
			if (it->revents & POLLERR)
			{
				errnum_len = sizeof (errnum);
				getsockopt(it->fd, SOL_SOCKET, SO_ERROR, &errnum, &errnum_len);
				this->logger.log(ERROR, std::string("Error on socket ") + it->fd + ": " + std::strerror(errnum));
				// TODO remove client and pollfd
			}
			else if (it->revents & POLLIN)
			{
				if (it->fd == _socketfd)
					this->__acceptClient();
				else if (__readFromClient(it->fd))
				{
					for (clientIt = this->clients.begin(); clientIt != this->clients.end(); ++it)
					{
						if (clientIt->sock_fd == it->fd)
						{
							this->clients.erase(clientIt);
							break;
						}
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
	if (!KEEP_RUNNING)
		this->__shutdown();
}

void	Server::__socket(int port) {

	int	val = 1;
	_socketfd = socket(AF_INET, SOCK_STREAM, 0);
	if (_socketfd == -1)
		throw Server::IoException("socket", errno);
	this->logger.log(DEBUG, "Socket created");
	if (setsockopt(_socketfd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof val))
		throw Server::IoException("used_address", errno);

	sockaddr_in	serv_addr;
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);

	if (bind(_socketfd, (sockaddr*)&serv_addr, sizeof(serv_addr)) != 0)
		throw Server::IoException("bind", errno);
	this->logger.log(DEBUG, "Socket bound");
	if (listen(_socketfd, SOMAXCONN) != 0)
		throw Server::IoException("listen", errno);
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
	this->commands.put("CAP", NULL);
	this->commands.put("PASS", cmd_pass);
	this->commands.put("USER", cmd_user);
	this->commands.put("NICK", cmd_nick);
	this->commands.put("QUIT", cmd_quit, CLIENT_STATE_LOGGED);
	this->commands.put("MOTD", cmd_motd, CLIENT_STATE_LOGGED);
	this->commands.put("OPER", cmd_oper, CLIENT_STATE_LOGGED);
	this->commands.put("JOIN", cmd_join, CLIENT_STATE_LOGGED);
	this->commands.put("PART", cmd_part, CLIENT_STATE_LOGGED);
	this->commands.put("DIE", cmd_die, CLIENT_STATE_LOGGED);
	this->commands.put("KILL", cmd_kill, CLIENT_STATE_LOGGED);
	this->commands.put("NOTICE", cmd_msg_common, CLIENT_STATE_LOGGED);
	this->commands.put("PRIVMSG", cmd_msg_common, CLIENT_STATE_LOGGED);
	this->commands.put("PING", cmd_ping);
	this->commands.put("PONG", cmd_pong);
}

void Server::processCommand(Client& client, std::string const& line)
{
	std::string prefix;
	std::string params;
	std::string::const_iterator begin;
	std::string::const_iterator it;

	if (line.empty())
		return;
	begin = line.begin();

	// extract prefix if any
	if (*begin == ':')
	{
		it = std::find(begin, line.end(), ' ');
		prefix = std::string(begin, it);
		begin = it;
		if (begin != line.end())
			++begin;
	}

	// extract command name
	it = std::find(begin, line.end(), ' ');

	// extract the rest of the line if any
	if (it != line.end())
		params = std::string(it + 1, line.end());

	// std::cout
	// 	<< std::setfill(' ')
	// 	<< " " GREEN "< INPUT" END "  " WHITE "|" END " " YELLOW
	// 	<< std::setw(15) << std::left
	// 	<< client.address << END " " WHITE "|" END " " GREEN
	// 	<< line << END << "\r\n";
	// execute the command with the given arguments
	this->commands.dispatch(client, prefix, std::string(begin, it), params);
}

void Server::removeClient(Client& client)
{
	ClientList::iterator clientIt;
	PollFdList::iterator pollfdIt;

	clientIt = std::find(this->clients.begin(), this->clients.end(), client);
	if (clientIt != this->clients.end())
	{
		for (pollfdIt = this->_clientfd.begin(); pollfdIt != this->_clientfd.end(); ++pollfdIt)
		{
			if (pollfdIt->fd == clientIt->sock_fd)
			{
				this->_clientfd.erase(pollfdIt);
				break;
			}
		}
		this->clients.erase(clientIt);
	}
	else
	{
		// TODO log error
	}
}

bool Server::addNickname(std::string const& nickname)
{
	return this->nicknames.insert(nickname).second;
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
		while (std::getline(in, line))
		{
			ss << line;
			ss >> entry.name >> entry.host >> entry.password;
			ss.clear();
			this->operatorPasswords.push_back(entry);
		}
	}
	else
	{
		this->logger.log(WARNING, "Failed to load operator file '" + file + "'");
		this->logger.log(WARNING, "There will be no operator for this server!");
	}
}

Client* Server::getClient(int fd)
{
	ClientList::iterator it;

	for (it = this->clients.begin(); it != this->clients.end(); ++it)
		if (it->sock_fd == fd)
			return &*it;
	return NULL;
}

Client* Server::getClient(std::string const& nickname)
{
	ClientList::iterator it;

	for (it = this->clients.begin(); it != this->clients.end(); ++it)
		if (it->nickname == nickname)
			return &*it;
	return NULL;
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
		return this->getClient(identifier); // TODO does not work :(
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

	Client client = Client(*this, fd, address);

	this->clients.push_back(client);

	pollfd newPollFd;

	newPollFd.fd = fd;
	newPollFd.events = POLLIN | POLLOUT;

	this->_newConnections.push_back(newPollFd);
}

bool Server::__readFromClient(int fd)
{
	Client* client;

	client = this->getClient(fd);
	if (client != NULL)
		return client->readFrom();
	this->logger.log(ERROR, std::string("No such client for socket file descriptor ") + fd);
	return false;
}

void Server::__writeToClient(int fd)
{
	Client* client;

	client = this->getClient(fd);
	if (client != NULL)
		client->writeTo();
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
	ClientList::iterator it;

	this->logger.log(INFO, "Shutting down...");
	for (it = this->clients.begin(); it != this->clients.end(); ++it)
		::close(it->sock_fd);
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
