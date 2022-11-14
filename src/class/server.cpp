/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 13:41:32 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/14 18:48:47 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "class/server.hpp"
#include "class/exception/io_exception.hpp"
#include "ft_irc.h"
#include <cerrno>
#include <ctime>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/epoll.h>

#include <iostream>

using irc::server;

server::server() :
	_port(),
	_password(),
	_start_time(),
	_sock_fd(-1),
	_epoll_fd(-1)
{}

server::server(::uint16_t port, std::string const& password) :
	_port(port),
	_password(password),
	_start_time(),
	_sock_fd(-1),
	_epoll_fd(-1)
{}

server::server(server const& x) :
	_port(x._port),
	_password(x._password),
	_start_time(),
	_sock_fd(-1),
	_epoll_fd(-1)
{}

server& server::operator=(server const& x)
{
	this->_port = x._port;
	this->_password = x._password;
	this->_start_time = x._start_time;
	this->_sock_fd = x._sock_fd;
	this->_epoll_fd = x._epoll_fd;
	return *this;
}

server::~server()
{
	this->__cleanup();
}

void server::start()
{
	std::cout << "Starting...\n";
	this->__socket();
	this->__epoll();
	this->__setup_addr();
	this->__bind();
	this->__listen();
	this->__splash();
	this->__run();
}

bool server::check_password(std::string const& password)
{
	return this->_password == password;
}

// create the socket
void server::__socket()
{
	int fd;

	fd = ::socket(PF_INET, SOCK_STREAM, 0);
	if (fd == -1)
		throw irc::io_exception("socket", errno);
	this->_sock_fd = fd;
}

// create epoll
void server::__epoll()
{
	int fd;

	fd = ::epoll_create1(0);
	if (fd == -1)
		throw irc::io_exception("epoll_create1", errno);
	this->_epoll_fd = fd;
	this->_event.data.fd = this->_sock_fd;
	this->_event.events = EPOLLIN | EPOLLET;
	this->__add_fd(this->_sock_fd);
}

// fill the sockaddr_in struct values
void server::__setup_addr()
{
	this->_addr.sin_addr.s_addr = INADDR_ANY; // TODO add configurable address
	this->_addr.sin_family = AF_INET;
	this->_addr.sin_port = ::htons(this->_port);
}

// bind it to an address
void server::__bind()
{
	int const val = 1;
	int res;

	// give the address back to the system once the socket is closed
	res = ::setsockopt(this->_sock_fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof (val));
	if (res == -1)
		throw irc::io_exception("setsockopt", errno);

	res = ::bind(this->_sock_fd, reinterpret_cast< ::sockaddr* >(&this->_addr), sizeof (this->_addr)); // TODO make this prettier
	if (res == -1)
		throw irc::io_exception("bind", errno);
}

// start listening
void server::__listen()
{
	int res;

	res = ::listen(this->_sock_fd, 10); // TODO add configurable backlog size
	if (res == -1)
		throw irc::io_exception("listen", errno);
}

// print some information on stdout
void server::__splash()
{
	std::cout << "Listening on " << ::inet_ntoa(this->_addr.sin_addr) << ":" << this->_port << '\n';
}

void server::__run()
{
	int count;
	int errnum;
	::epoll_event events[20]; // TODO maybe add dynamic array

	while (true)
	{
		// wait for ready file descriptors
		count = ::epoll_wait(this->_epoll_fd, events, 20, -1); // TODO maybe add dynamic array
		std::cout << "ready: " << count << '\n';

		if (count == -1)
		{
			errnum = errno;
			// not interrupted by a signal
			if (errnum != EINTR)
				throw irc::io_exception("epoll_wait", errnum);
			break;
		}

		// loop through ready file descriptors
		for (int i = 0; i < count; ++i)
		{
			if (events[i].events & EPOLLIN)
			{
				// ready for read operation
				if (events[i].data.fd == this->_sock_fd)
				{
					int fd;
					::sockaddr_in addr;
					::socklen_t addr_len;

					addr_len = sizeof (addr);

					fd = ::accept(this->_sock_fd, reinterpret_cast< ::sockaddr* >(&addr), &addr_len);
					if (fd == -1)
					{
						errnum = errno;
						std::cerr << "Stream error: " << std::strerror(errnum) << '\n';
					}
					else
					{
						this->__add_fd(fd);
						std::cout << "Accepted " << fd << " from " << ::inet_ntoa(addr.sin_addr) << '\n';
					}
				}
				else
				{
					char buffer[10];
					int rd;

					rd = ::recv(events[i].data.fd, buffer, sizeof (buffer), 0);
					if (rd > 0)
						write(1, buffer, rd);
					else
					{
						errnum = errno;
						if (rd == -1)
							std::cerr << "Stream error: " << std::strerror(errnum) << '\n';
						else
							std::cout << "End of stream" << '\n';
						::close(events[i].data.fd);
					}
				}

			}
			if (events[i].events & EPOLLOUT)
			{
				// ready for write operation
			}
		}
	}
}

void server::__add_fd(int fd)
{
	int res;

	res = ::epoll_ctl(this->_epoll_fd, EPOLL_CTL_ADD, fd, &this->_event);
	if (res == -1)
		throw irc::io_exception("epoll_ctl", errno);
}

void server::__remove_fd(int fd)
{
	int res;

	res = ::epoll_ctl(this->_epoll_fd, EPOLL_CTL_DEL, fd, &this->_event);
	if (res == -1)
		throw irc::io_exception("epoll_ctl", errno);
}

void server::__cleanup()
{
	if (this->_epoll_fd != -1)
		::close(this->_epoll_fd);
	if (this->_sock_fd != -1)
		::close(this->_sock_fd);
}
