/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 22:19:18 by bbrassar          #+#    #+#             */
/*   Updated: 2022/12/19 18:10:33 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

#include "config.h"

#include <cstring>
#include <ctime>

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <unistd.h>

/* ==========================================================================
								COPLIEN FORM
   ========================================================================== */

Client::Client(Server* server) : Recipient(server),
	channels(),
	username(),
	hostname(),
	realname(),
	sock_fd(-1),
	address(),
	readBuffer(),
	writeBuffer(),
	password(),
	shouldClose(false),
	hasQuit(false),
	isInvisible(false),
	_state(CLIENT_STATE_INIT)
{}

Client::Client(Server* server, int fd, sockaddr_in& addr) : Recipient(server),
	channels(),
	username(),
	hostname(),
	realname(),
	sock_fd(fd),
	address(addr),
	readBuffer(),
	writeBuffer(),
	password(),
	shouldClose(false),
	hasQuit(false),
	isInvisible(false),
	_state(CLIENT_STATE_INIT)
{}

Client::~Client() {}

Client::Client(Client const &src) : Recipient(src.server) {
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
		this->shouldClose = rhs.shouldClose;
		this->hasQuit = rhs.hasQuit;
		this->isInvisible = rhs.isInvisible;
	}
	return (*this);
}

/* ==========================================================================
								MEMBERS FUNCTIONS
   ========================================================================== */

bool Client::readFrom()
{
	int errnum;
	int res;
	char bytes[2048];

	res = ::recv(this->sock_fd, bytes, sizeof (bytes), 0);
	if (res == -1)
	{
		errnum = errno;
		this->server->logger.log(ERROR, "<" + address + "> Unable to recv: " + std::strerror(errnum));
		this->closeConnection();
		return true;
	}

	if (res == 0)
	{
		// connection has been closed by client
		this->server->logger.log(DEBUG, "<" + address + "> Connection closed by client");
		this->closeConnection();
		return true;
	}

	this->server->logger.log(DEBUG, "<" + address + "> Read " + res + " bytes of data");
	this->readBuffer += std::string(&bytes[0], &bytes[res]); // range constructor
	this->__processReadBuffer();
	return false;
}

void Client::flushWriteBuffer()
{
	int errnum;
	int res;

	if (this->writeBuffer.empty())
		return;
	res = ::send(this->sock_fd, this->writeBuffer.c_str(), this->writeBuffer.size(), 0);
	if (res == -1)
	{
		errnum = errno;
		std::cerr << "Error: unable to send to " << this->address << ": " << ::strerror(errnum) << '\n';
		this->shouldClose = true;
		return;
	}
	this->server->logger.log(DEBUG, "<" + this->address + "> Sent " + res + " bytes of data");
	this->writeBuffer.clear();
}

void Client::send(std::string const& command) {
	this->writeBuffer += command + "\r\n";
	this->server->logger.log(DEBUG, "SEND <" + this->address + "> '" + command + "'");
	// std::cout << std::setfill(' ') << RED " > OUTPUT" END " " WHITE "|" END " " YELLOW << std::left << std::setw(15) << this->address << END " " WHITE "|" END " " RED << command << END << "\r\n";
}

void Client::closeConnection() {
	::close(this->sock_fd);
	// std::cout << std::setfill(' ') << YELLOW " * CLOSED" END " " WHITE "|" END " " YELLOW << std::left << std::setw(15) << this->address << END " " WHITE "|" END << "\r\n";
}

void Client::tryLogin()
{
	if (this->checkState(CLIENT_STATE_LOGGED))
	{
		if (this->password == this->server->password)
		{
			this->reply<RPL_WELCOME>(this->nickname, this->username, "" + this->address);
			this->reply<RPL_YOURHOST>();
			this->reply<RPL_CREATED>(this->server->startDate);
			this->reply<RPL_MYINFO>(SERVER_NAME);
			this->server->logger.log(DEBUG, "<" + this->address + "> Logged in as " + this->asPrefix());
			this->server->sendMotd(*this);
			if (this->checkState(CLIENT_STATE_NICK_FAILED))
				this->send(this->asPrefix() + " NICK " + this->nickname);
		}
		else
		{
			this->server->logger.log(DEBUG, "<" + this->address + "> Wrong password");
			// this->reply<ERR_PASSWDMISMATCH>();
			this->send("ERROR :Wrong password");
			this->shouldClose = true;
		}
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

void Client::sendMessage(Client& sender, std::string const& command, std::string const& message)
{
	this->send(sender.asPrefix() + " " + command + " " + this->nickname + " :" + message);
}

void Client::__replyRaw(Reply code, std::string const& message)
{
	std::stringstream ss;

	ss << std::setfill('0') << std::setw(3) << code << std::setw(0) << ' ' << message << "\r\n";
	this->writeBuffer += ss.str();
}

void Client::__processReadBuffer()
{
	std::string::size_type offset;
	std::string::iterator it;
	std::string line;

	do
	{
		it = this->readBuffer.begin();
		offset = this->readBuffer.find("\r\n");
		if (offset == std::string::npos)
			break;
		line = std::string(it, it + offset);
		this->readBuffer = this->readBuffer.substr(offset + 2);
		this->server->commandMap.process(*this, line);
	} while (it != this->readBuffer.end());
}

void Client::__log(LogLevel level, std::string const& message)
{
	this->server->logger.log(level, "<" + this->address + "> " + message);
}

bool operator==(Client const& lhs, Client const& rhs)
{
	return &lhs == &rhs || lhs.sock_fd == rhs.sock_fd || lhs.nickname == rhs.nickname;
}

bool operator!=(Client const& lhs, Client const& rhs)
{
	return !(lhs == rhs);
}
