/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 14:00:38 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/16 19:31:32 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

/* ==========================================================================
								COPLIEN AFORM 
   ========================================================================== */

Channel::Channel() : name("default") {}

Channel::Channel(std::string name, std::string passwd): name(name), passwd(passwd) {}

Channel	&Channel::operator=() {
	
	if (this != &rhs) {

		server = rhs.server;
		allClients = rhs.allClients;
		name = rhs.name;
		topic = rhs.topic;
		passwd = rhs.passwd;
	}
	return (*this);	
}

/* ==========================================================================
								MEMBER FUNCTIONS 
   ========================================================================== */

void	Channel::broadcast(Client &sender, std::string const msg) {
	
	ClientList::iterator	i = allClients.begin();

	for (; i != allClients.end(); i++) {
		if (&sender != *i)
			std::cout << sender.nickname << ": \"" << msg << "\"";
	 }
	 // MUST REDIRECT STREAM
}

void 	Channel::addClient(Client &newClient) {
	allClients.insert(&newCLient);
}

void Channel::removeClient(Client &client) {
	allClients.erase(&client);
}

bool Channel::hasClient(Client &client) {
	
	ClientList::iterator	i = allClients.begin();

	for (; i != allClients.end(); i++) {
		if (&client != *i)
			return true;
	 }
	return false;
}
