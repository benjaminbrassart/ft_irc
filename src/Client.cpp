/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 22:19:18 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/16 19:19:48 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include <iostream>

/* ==========================================================================
								COPLIEN FORM 
   ========================================================================== */

Client::Client() : isOpe(false), isLogged(false) {}

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

void Client::reply(Reply code, std::string const& message) {
	// TODO send to socket
	std::cout << "Server -> Client |   " << code << " \"" << message << "\"\n";
}

void Client::send(std::string const& command) {
	// TODO send to socket
	std::cout << "Server -> Client |   " << command << '\n';
}

void Client::closeConnection() {
	// TODO close socket
	std::cout << "Server terminated connection to client\n";
}
