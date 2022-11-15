/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estoffel <estoffel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 20:05:51 by estoffel          #+#    #+#             */
/*   Updated: 2022/11/15 22:41:18 by estoffel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server() {}

Server::~Server() {}

Server::IoException::IoException(String const& syscall, int err): _what(syscall + ": " + std::strerror(err)) {}

Server::IoException::~IoException() throw() {}

const char*	Server::IoException::what() const throw() {

	return this->_what.c_str();
}

bool	Server::create_socket() {

	_socketfd = socket(AF_INET, SOCK_STREAM, 0);
	if (_socketfd != 0) {
		std::cerr << "Error trying to create a socket" << std::endl;
		return false;
	}
	return true;
}

