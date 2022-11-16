/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 14:00:38 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/16 18:57:35 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

/* ==========================================================================
								COPLIEN AFORM 
   ========================================================================== */

Channel::Channel() : _name("default") {}

Channel::Channel(std::string name, std::string passwd): _name(name), _passwd(passwd) {}

Channel	&Channel::operator=() {
	
	if (this != &rhs) {

		server = rhs._server;
		_clients = rhs._clients;
		_name = rhs._name;
		_topic = rhs._topic;
		_passwd = rhs._passwd;
	}
	return (*this);	
}

/* ==========================================================================
								MEMBER FUNCTIONS 
   ========================================================================== */

void	Channel::broadcast(Client &sender, std::string const msg) {
	
	ClientList::iterator	i = _clients.begin();

	for (; i != _clients.end(); i++) {
		if (&sender != *i)
			std::cout << sender.nickname << ": \"" << msg << "\"";
	 }
	 // MUST REDIRECT STREAM
}

void 	Channel::addClient(Client &newClient) {
	_clients.insert(&newCLient);
}

void Channel::removeClient(Client &client) {
	_clients.erase(&client);
}

bool Channel::hasClient(Client &client) {
	
	ClientList::iterator	i = _clients.begin();

	for (; i != _clients.end(); i++) {
		if (&clients != *i)
			return true;
	 }
	return false;
}
