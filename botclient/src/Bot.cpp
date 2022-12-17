/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estoffel <estoffel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 07:57:33 by estoffel          #+#    #+#             */
/*   Updated: 2022/12/17 15:11:29 by estoffel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bot.hpp"
#include <cstring>
#include <cerrno>
#include <unistd.h>

Bot::Bot(): clientFd(-1) {}

Bot::Bot(Bot const& cpy): clientFd(cpy.clientFd) {}

Bot&	Bot::operator=(Bot const& asgn)
{
	this->clientFd = asgn.clientFd;
	return *this;
}

Bot::~Bot() {}

Bot::IOException::IOException(std::string const& syscallName, int errnum) :
	_reason(syscallName + ": " + std::strerror(errnum)) {}

Bot::IOException::~IOException() throw() {}

char const* Bot::IOException::what() const throw()
{
	return this->_reason.c_str();
}

Bot::IOException::IOException(std::string const& syscallName, std::string const& msg) :
	_reason(syscallName + ": " + msg) {}

void	Bot::connectClient(const char* hostname, const char* port) {

	::addrinfo addr = {};
	::addrinfo *results;
	::addrinfo *record;
	addr.ai_family = AF_INET;
	addr.ai_socktype = SOCK_STREAM;
	addr.ai_protocol = IPPROTO_TCP;

	int	gai_codenbr;

	gai_codenbr = getaddrinfo(hostname, port, &addr, &results);
	if ( gai_codenbr != 0) {
		throw IOException("getaddrinfo", gai_strerror(gai_codenbr));
	}
	for (record = results; record != NULL; record = record->ai_next) {
		clientFd = socket(record->ai_family, record->ai_socktype, record->ai_protocol);
		if (clientFd == -1)
			continue ;
		if (connect(clientFd, record->ai_addr, record->ai_addrlen) != -1)
			break ;
		close(clientFd);
	}
	freeaddrinfo(results);
	if (record == NULL) {
		throw IOException("connect", "unable to create or connect client socket");
	}
}
