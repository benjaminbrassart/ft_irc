/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 22:19:18 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/25 03:13:16 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include <ctime>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>

int const Client::READ_BUFFER_SIZE = 2048;

/* ==========================================================================
								COPLIEN FORM
   ========================================================================== */

Client::Client(Server& server) :
	server(&server),
	sock_fd(-1),
	_state(CLIENT_STATE_INIT)
{}

Client::Client(Server& server, int fd, sockaddr_in& addr) :
	server(&server),
	sock_fd(fd),
	address(addr),
	_state(CLIENT_STATE_INIT)
{}

Client::~Client() {}

Client::Client(Client const &src) {
	*this = src;
}

Client		&Client::operator=(Client const &rhs) {

	if (this != &rhs) {

		this->_state = rhs._state;
		this->server = rhs.server;
		this->channels = rhs.channels;
		this->username = rhs.username;
		this->hostname = rhs.hostname;
		this->realname = rhs.realname;
		this->sock_fd = rhs.sock_fd;
		this->nickname = rhs.nickname;
		this->address = rhs.address;
	}
	return (*this);
}

/* ==========================================================================
								MEMBERS FUNCTIONS
   ========================================================================== */

void Client::quit(std::string const& message)
{
	Server& server = *this->server;
	Server::ClientList::const_iterator it;

	(void)message;
	for (it = server.clients.begin(); it != server.clients.end(); ++it)
	{
		if (&*it != this)
		{
			// TODO
		}
	}
}

void Client::readFrom()
{
	{
		int res;
		char bytes[2048];

		res = ::recv(this->sock_fd, bytes, sizeof (bytes), 0);
		if (res == -1)
		{
			// TODO log error
		}
		else if (res == 0)
		{
			// connection has been closed by client
			this->closeConnection();
			this->server->clients.erase(*this);
		}
		else
		{
			// TODO log what was read (into log file)
			this->readBuffer += std::string(&bytes[0], &bytes[res]); // range constructor
			this->__processReadBuffer();
		}
	}
}

void Client::writeTo()
{
	int res;

	res = ::send(this->sock_fd, this->writeBuffer.c_str(), this->writeBuffer.size(), 0);
	if (res == -1)
	{
		// TODO log error
		return;
	}
	this->writeBuffer.clear();
}

void Client::send(std::string const& command) {
	// TODO send to socket
	this->writeBuffer += command + "\r\n";
	std::cout << "Server -> Client |   " << command << '\n';
}

void Client::closeConnection() {
	// TODO close socket
	std::cout << "Server terminated connection to client\n";
}

void Client::tryLogin()
{
	if (this->checkState(CLIENT_STATE_LOGGED))
	{
		this->reply<RPL_WELCOME>(this->nickname, this->username, this->hostname);
		this->reply<RPL_YOURHOST>();
		this->reply<RPL_CREATED>(this->server->startDate);
		this->reply<RPL_MYINFO>(this->server->name);
	}
}

bool Client::checkState(ClientState state)
{
	return (this->_state & state) == state;
}

void Client::setState(ClientState state)
{
	this->_state |= state;
}

void Client::sendMotd()
{
	std::ifstream file;
	std::string line;

	file.open(this->server->motdFileName.c_str());

	if (file)
	{
		this->reply<RPL_MOTDSTART>(this->server->name);
		while (std::getline(file, line))
			this->reply<RPL_MOTD>(line.substr(0, 80));
		this->reply<RPL_ENDOFMOTD>();
	}
	else
		this->reply<ERR_NOMOTD>();
}

void Client::joinChannel(Channel& channel)
{
	Channel::ClientList::iterator it;
	std::string const prefix = this->asPrefix();

	channel.addClient(*this);
	for (it = channel.allClients.begin(); it != channel.allClients.end(); ++it)
		(*it)->send(prefix + " JOIN :" + channel.name);
	this->reply<RPL_TOPIC>(channel.name, channel.topic);
}

void Client::leaveChannel(Channel& channel, std::string const& message)
{
	Channel::ClientList::iterator it;

	channel.removeClient(*this);
	this->channels.erase(&channel);

	if (channel.allClients.empty())
	{
		// TODO delete channel
	}
	else
	{
		std::string const prefix = this->asPrefix();

		for (it = channel.allClients.begin(); it != channel.allClients.end(); ++it)
			(*it)->send(prefix + " PART " + channel.name + " :" + message);
	}
}

void Client::leaveAllChannels(std::string const& message)
{
	ChannelList::iterator it;

	for (it = this->channels.begin(); it != this->channels.end(); ++it)
		leaveChannel(const_cast<Channel&>(**it), message);
}

std::string Client::asPrefix()
{
	std::stringstream ss;

	ss << ':' << this->nickname << '!' << this->username << '@' << this->address;
	return ss.str();
}

void Client::__replyRaw(Reply code, std::string const& message)
{
	std::stringstream ss;

	ss << std::setfill('0') << std::setw(3) << code << std::setw(0) << ' ' << message << "\r\n";
	std::cout << std::setfill(' ') << " \033[31m> OUTPUT\033[0m \033[37m|\033[0m " << "\033[33m" << std::left << std::setw(15) << this->address << "\033[0m" << " \033[37m|\033[0m " << "\033[36m" << std::setfill('0') << std::setw(3) << std::right << code << "\033[0m" << std::setw(0) << ' ' << message << "\r\n";

	// std::cout << "> " << std::setfill('0') << std::setw(3) << code << " \"" << message << "\"\n";
	this->writeBuffer += ss.str();
}

void Client::__processReadBuffer()
{
	std::string::size_type offset;
	std::string::iterator it;

	it = this->readBuffer.begin();
	while (it != this->readBuffer.end())
	{
		offset = this->readBuffer.find("\r\n");
		if ((it + offset) == this->readBuffer.end())
		{
			this->readBuffer = std::string(it, it + offset);
			break;
		}
		this->server->processCommand(*this, std::string(it, it + offset));
		it += (offset + 2);
	}
}
