/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 20:05:51 by estoffel          #+#    #+#             */
/*   Updated: 2022/11/29 13:14:41 by bbrassar         ###   ########.fr       */
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
	clients(),
	logger(Logger::DEBUG)
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

void	Server::create_socket(int port) {

	int	val = 1;
	_socketfd = socket(AF_INET, SOCK_STREAM, 0);
	if (_socketfd == -1)
		throw Server::IoException("socket", errno);
	std::cout << "* socket created * ✅ " << "\n";
	if (setsockopt(_socketfd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof val))
		throw Server::IoException("used_address", errno);
	sockaddr_in	serv_addr;
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);
	if (bind(_socketfd, (sockaddr*)&serv_addr, sizeof(serv_addr)) != 0)
		throw Server::IoException("bind", errno);
	std::cout << "* socket bound * ✅ " << "\n";
	if (listen(_socketfd, SOMAXCONN) != 0)
		throw Server::IoException("listen", errno);
	std::cout << "* listening to client * ✅ " << "\n";
	pollfd	fd_serv;
	bzero((int *) &fd_serv, sizeof(fd_serv));
	fd_serv.fd = _socketfd;
	fd_serv.events = POLLIN;
	_clientfd.push_back(fd_serv);
	int	poll_ret;
	while (this->_running) {
		poll_ret = poll(&*_clientfd.begin(), _clientfd.size(), -1);
		if (poll_ret == -1)
		{
			if (errno == EINTR)
			{
				std::cout << '\n' << "Shutting down gracefully, press Ctrl+C again to force." << '\n';
				break;
			}
			throw Server::IoException("poll", errno); // TODO: gerer les signaux
		}
		std::vector<pollfd>::const_iterator	it;
		for (it = _clientfd.begin(); it != _clientfd.end(); it++) {
			if (it->revents & POLLERR)
			{
				std::cerr << "Error on fd " << it->fd << '\n';
				continue;
			}
			if (it->revents & POLLIN) {
				if (it->fd == _socketfd)
					__acceptClient();
				else
					__readFromClient(it->fd);
			}
			if (it->revents & POLLOUT)
				__writeToClient(it->fd);
		}
		this->_clientfd.insert(this->_clientfd.end(), this->_newConnections.begin(), this->_newConnections.end());
		this->_newConnections.clear();
	}
	// sockaddr_in	client_add;
	// socklen_t client_taille = sizeof(client_add);
	// _clientfd = accept(_socketfd, (sockaddr*)&client_add, &client_taille);
	// if (_clientfd == -1)
	// 	throw Server::IoException("client", errno);
	// std::cout << "* client accepted * ✅ " << "\n";
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
	this->commands.put("USER", cmd_user, CLIENT_STATE_PASS);
	this->commands.put("NICK", cmd_nick, CLIENT_STATE_PASS);
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
	this->_running = false;
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
	sockaddr_in address;
	socklen_t addressLength;

	addressLength = sizeof (address);
	fd = ::accept(this->_socketfd, (sockaddr*)&address, &addressLength);

	if (fd == -1)
	{
		// TODO log error, do not throw an exception because this is not fatal
		return;
	}

	Client client = Client(*this, fd, address);

	if (this->password.empty())
		client.setState(CLIENT_STATE_PASS);

	this->clients.push_back(client);

	pollfd newPollFd;

	newPollFd.fd = fd;
	newPollFd.events = POLLIN | POLLOUT;

	this->_newConnections.push_back(newPollFd);
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
