/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 20:05:51 by estoffel          #+#    #+#             */
/*   Updated: 2022/11/17 20:47:46 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include <cerrno>

Server::Server() {}

Server::~Server() {}

Server::IoException::IoException(string const& syscall, int err): _what(syscall + ": " + std::strerror(err)) {}

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

bool ChannelComparator::operator()(Channel const& lhs, Channel const& rhs)
{
	return lhs.name < rhs.name;
}
