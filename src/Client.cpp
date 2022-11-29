/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 22:19:18 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/29 08:14:14 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include <ctime>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>

/* ==========================================================================
								COPLIEN FORM
   ========================================================================== */

Client::Client(Server& server) : Recipient(server),
	sock_fd(-1),
	_state(CLIENT_STATE_INIT)
{}

Client::Client(Server& server, int fd, sockaddr_in& addr) : Recipient(server),
	sock_fd(fd),
	address(addr),
	_state(CLIENT_STATE_INIT)
{}

Client::~Client() {}

Client::Client(Client const &src) : Recipient(*src.server) {
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
	(void)message;
	// TODO
}

void Client::readFrom()
{
	int errnum;
	int res;
	char bytes[2048];

	res = ::recv(this->sock_fd, bytes, sizeof (bytes), 0);
	if (res == -1)
	{
		errnum = errno;
		std::cerr << "Error: unable to recv from " << this->address << ": " << ::strerror(errnum) << '\n';
	}
	else if (res == 0)
	{
		// connection has been closed by client
		this->closeConnection();
		this->server->removeClient(*this);
	}
	else
	{
		// TODO log what was read (into log file)
		this->readBuffer += std::string(&bytes[0], &bytes[res]); // range constructor
		this->__processReadBuffer();
	}
}

void Client::writeTo()
{
	int errnum;
	int res;

	res = ::send(this->sock_fd, this->writeBuffer.c_str(), this->writeBuffer.size(), 0);
	if (res == -1)
	{
		errnum = errno;
		std::cerr << "Error: unable to send to " << this->address << ": " << ::strerror(errnum) << '\n';
		return;
	}
	this->writeBuffer.clear();
}

void Client::send(std::string const& command) {
	this->writeBuffer += command + "\r\n";

	std::cout << std::setfill(' ') << RED " > OUTPUT" END " " WHITE "|" END " " YELLOW << std::left << std::setw(15) << this->address << END " " WHITE "|" END " " RED << command << END << "\r\n";
}

void Client::closeConnection() {
	::close(this->sock_fd);
	std::cout << std::setfill(' ') << YELLOW " * CLOSED" END " " WHITE "|" END " " YELLOW << std::left << std::setw(15) << this->address << END " " WHITE "|" END << "\r\n";
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

void Client::leaveChannel(Channel& channel, std::string const& message)
{
	std::string const prefix = this->asPrefix();
	Channel::ClientList::iterator it;

	channel.removeClient(*this);
	this->channels.erase(&channel);

	for (it = channel.allClients.begin(); it != channel.allClients.end(); ++it)
		it->client->send(prefix + " PART " + channel.name + " :" + message);
}

void Client::leaveAllChannels(std::string const& message)
{
	ChannelList::iterator it;

	for (it = this->channels.begin(); it != this->channels.end(); ++it)
		leaveChannel(**it, message);
}

std::string Client::asPrefix()
{
	std::stringstream ss;

	ss << ':' << this->nickname << '!' << this->username << '@' << this->address;
	return ss.str();
}

std::string const& Client::getIdentifier() const
{
	return this->nickname;
}

void Client::sendMessage(Client& sender, std::string const& message)
{
	(void)sender;
	(void)message;
	// TODO
}

void Client::__replyRaw(Reply code, std::string const& message)
{
	std::stringstream ss;

	ss << std::setfill('0') << std::setw(3) << code << std::setw(0) << ' ' << message << "\r\n";
	std::cout << std::setfill(' ') << RED " > OUTPUT" END " " WHITE "|" END " " YELLOW << std::left << std::setw(15) << this->address << END " " WHITE "|" WHITE " " RED_BG << std::setfill('0') << std::setw(3) << std::right << code << END << std::setw(0) << " " RED << message << END << "\r\n";

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
