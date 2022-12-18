/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estoffel <estoffel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 20:05:51 by estoffel          #+#    #+#             */
/*   Updated: 2022/12/17 13:00:11 by estoffel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

#include "config.h"
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
	logger(Logger(DEBUG)),
	startDate(Server::__getStartDate()),
	commandMap(*this)
 {}

Server::~Server() {}

void	Server::createSocket(int port)
{
	int const optval = 1;
	::sockaddr_in addr = {
		.sin_family = AF_INET,
		.sin_port = ::htons(port),
		.sin_addr = { .s_addr = ::htonl(INADDR_ANY) },
		.sin_zero = { },
	};

	this->sockFd = ::socket(AF_INET, SOCK_STREAM, 0);
	if (this->sockFd == -1)
		throw IOException("socket", errno);
	this->logger.log(DEBUG, "Socket created");

	if (::setsockopt(sockFd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof (optval)) == -1)
		throw IOException("setsockopt(SO_REUSEADDR)", errno);

	if (::bind(sockFd, reinterpret_cast< ::sockaddr* >(&addr), sizeof(addr)) == -1)
		throw IOException("bind", errno);
	this->logger.log(DEBUG, "Socket bound");

	if (listen(sockFd, SOMAXCONN) == -1)
		throw IOException("listen", errno);
	this->logger.log(INFO, std::string("Listening on port ") + port);
}

void Server::start()
{
	this->connectionManager.setServer(*this);

	while (g_Mode == 1)
	{
		this->connectionManager.wait();
		this->connectionManager.handlePoll(*this);
	}
	this->__shutdown();
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
		ChannelManager::iterator it = this->channelManager.getChannel(identifier);

		if (it != this->channelManager.end())
			return &*it;
	}
	else
	{
		NicknameManager::iterator it = this->nickManager.getClient(identifier);

		if (it != this->nickManager.end())
			return it->second;
	}
	return NULL;
}

void Server::sendMotd(Client& client)
{
	std::ifstream file;
	std::string line;

	file.open("motd.txt");
	if (file)
	{
		client.reply<RPL_MOTDSTART>(SERVER_NAME);
		while (std::getline(file, line))
			client.reply<RPL_MOTD>(line.substr(0, 80));
		client.reply<RPL_ENDOFMOTD>();
	}
	else
		client.reply<ERR_NOMOTD>();
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
