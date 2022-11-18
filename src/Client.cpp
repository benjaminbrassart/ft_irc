/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 22:19:18 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/18 22:37:03 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include <iostream>

int const Client::READ_BUFFER_SIZE = 2048;

/* ==========================================================================
								COPLIEN FORM
   ========================================================================== */

Client::Client() : isOpe(false), isLogged(false) {}

Client::Client(int fd, sockaddr_in& addr) :
	sock_fd(fd),
	address(addr)
{}

Client::~Client() {}

Client::Client(Client const &src) {
	*this = src;
}

Client		&Client::operator=(Client const &rhs) {

	if (this != &rhs) {

		server = rhs.server;
		channels = rhs.channels;
		password = rhs.password;
		info = rhs.info;
		sock_fd = rhs.sock_fd;
		isOpe = rhs.isOpe;
		isLogged = rhs.isLogged;
		nickname = rhs.nickname;
		address = rhs.address;
	}
	return (*this);
}

/* ==========================================================================
								MEMBERS FUNCTIONS
   ========================================================================== */

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
	std::cout << "Server -> Client |   " << command << '\n';
}

void Client::closeConnection() {
	// TODO close socket
	std::cout << "Server terminated connection to client\n";
}

void Client::__replyRaw(Reply code, std::string const& message)
{
	std::cout << "Server -> Client |   " << code << " \"" << message << "\"\n";
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
