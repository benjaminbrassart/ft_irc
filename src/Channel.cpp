/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 14:00:38 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/20 22:53:10 by lrandria         ###   ########.fr       */
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
}

bool 	Channel::addClient(ClientList list, Client &newClient) {
	
	ClientList::iterator	i = banned.begin();

	for (; i != banned.end(); i++)
		if (&newClient == *i)
			return false;					// to check with team
	return list.insert(&newClient).second;
}

bool Channel::removeClient(ClientList list, Client &client) {
	return list.erase(&client) > 0;
}

bool Channel::hasClient(ClientList list, Client &client) const {

	ClientList::iterator	i = list.begin();

	for (; i != list.end(); i++) {
		if (&client != *i)
			return true;
	 }
	return false;
}
