/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 22:19:18 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/16 14:10:29 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include <iostream> // TODO remove

Client::Client() :
	is_logged(false)
{}

Client::~Client()
{}

void Client::reply(Reply code, std::string const& message)
{
	// TODO send to socket
	std::cout << "Server -> Client |   " << code << " \"" << message << "\"\n";
}

void Client::send(std::string const& command)
{
	// TODO send to socket
	std::cout << "Server -> Client |   " << command << '\n';
}

void Client::closeConnection()
{
	// TODO close socket
	std::cout << "Server terminated connection to client\n";
}