/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 20:05:51 by estoffel          #+#    #+#             */
/*   Updated: 2022/11/25 11:26:47 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include <algorithm>
#include <cerrno>
#include <fstream>
#include <iomanip>
#include <sstream>

Server::Server() :
	startDate(Server::__getStartDate()),
	clients()
 {}

Server::~Server() {}

Server::IoException::IoException(std::string const& syscall, int err):
	_what(syscall + ": " + std::strerror(err)) {}

Server::IoException::~IoException() throw() {}

const int	&Server::getsocketfd() const {return this->_socketfd;}

const int	&Server::getclientfd() const {return this->_clientfd;}

const char*	Server::IoException::what() const throw() {

	return this->_what.c_str();
}

void	Server::create_socket(int port) {

	_socketfd = socket(AF_INET, SOCK_STREAM, 0);
	if (_socketfd != 0)
		throw Server::IoException("socket", errno);
	sockaddr_in	sockadd_in;
	sockadd_in.sin_addr.s_addr = htonl(INADDR_ANY);
	sockadd_in.sin_family = AF_INET;
	sockadd_in.sin_port = htons(port);
	if (bind(_socketfd, (sockaddr*)&sockadd_in, sizeof(sockadd_in)) != 0)
		throw Server::IoException("bind", errno);
	if (listen(_socketfd, SOMAXCONN) != 0)
		throw Server::IoException("listen", errno);
	sockaddr_in	client_add;
	socklen_t client_taille = sizeof(client_add);
	_clientfd = accept(_socketfd, (sockaddr*)&client_add, &client_taille);
	if (_clientfd == -1)
		throw Server::IoException("client", errno);
}

Server::ChannelList::iterator Server::getChannel(std::string const& channelName)
{
	ChannelList::iterator it;

	for (it = this->channels.begin(); it != this->channels.end(); ++it)
		if (it->name == channelName)
			break;
	return it;
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

	std::cout
		<< std::setfill(' ')
		<< " " GREEN "< INPUT" END "  " WHITE "|" END " " YELLOW
		<< std::setw(15) << std::left
		<< client.address << END " " WHITE "|" END " " GREEN
		<< line << END << "\r\n";
	// execute the command with the given arguments
	this->commands.dispatch(client, prefix, std::string(begin, it), params);
}

void Server::removeClient(Client& client)
{
	(void)client; // TODO
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
}

void Server::shutdown()
{
	// TODO
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
	std::cout << this->clients.size() << '\n';

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
	sockaddr_in address;
	socklen_t addressLength;

	addressLength = sizeof (address);
	fd = ::accept(this->_socketfd, (sockaddr*)&address, &addressLength);

	if (fd == -1)
	{
		// TODO log error, do not throw an exception because this is not fatal
		return;
	}

	this->clients.push_back(Client(*this, fd, address));
}

void Server::__readFromClient(int fd)
{
	Client* client;

	client = this->getClient(fd);
	if (client != NULL)
		client->readFrom();
	else
	{
		// TODO log error, client not found
	}
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

bool ClientComparator::operator()(Client const& lhs, Client const& rhs) const
{
	return lhs.sock_fd < rhs.sock_fd;
}

bool ChannelComparator::operator()(Channel const& lhs, Channel const& rhs) const
{
	return lhs.name < rhs.name;
}

std::ostream& operator<<(std::ostream& os, sockaddr_in& address)
{
	os << inet_ntoa(address.sin_addr);
	return os;
}
