/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 14:00:38 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/20 21:02:18 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

/* ==========================================================================
								COPLIEN AFORM
   ========================================================================== */

Channel::Channel() : name("default") {}

Channel::Channel(std::string name, std::string passwd): name(name), passwd(passwd) {}

Channel	&Channel::operator=(Channel const& rhs) {

	if (this != &rhs) {

		server = rhs.server;
		allClients = rhs.allClients;
		name = rhs.name;
		topic = rhs.topic;
		passwd = rhs.passwd;
	}
	return (*this);
}

Channel::~Channel()
{}

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

bool 	Channel::addClient(Client &newClient) {
	return allClients.insert(&newClient).second;
}

bool Channel::removeClient(Client &client) {
	return allClients.erase(&client) > 0;
}

bool Channel::hasClient(Client &client) const {
	return allClients.find(&client) != allClients.end();
}
