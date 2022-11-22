/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 14:00:38 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/22 16:02:10 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

/* ==========================================================================
								COPLIEN AFORM
   ========================================================================== */

Channel::Channel() : _owner("default"), _name("default") {}

Channel::Channel(Client &owner, std::string name) : _owner(owner.nickname) {
	
	setName(name);
	addClient(operators, owner);
}

Channel::Channel(Client &owner, std::string name, std::string passwd): _owner(owner.nickname),
																	   _passwd(passwd) {
	
	setName(name);
	addClient(operators, owner);
}

Channel	&Channel::operator=(Channel const& rhs) {

	if (this != &rhs) {

		server = rhs.server;
		allClients = rhs.allClients;
		operators = rhs.operators;
		banned = rhs.banned;
		_owner = rhs._owner;
		_name = rhs._name;
		_topic = rhs._topic;
		_passwd = rhs._passwd;
	}
	return (*this);
}

Channel::~Channel() {}

/* ==========================================================================
								MEMBER FUNCTIONS
   ========================================================================== */

bool	Channel::setName(std::string newName) {						// must change cerr for the right stream

	if (newName.size() > 50) {
		std::cerr << "error: channel name is too long.\n";
		return false;
	}
	else if (newName[0] != '&' || newName[0] != '#'|| newName[0] != '+' || newName[0] != '!') {
		std::cerr << "error: channel name requires a valid prefix.\n";
		return false;
	}
	else if (newName.find_first_of("\t\v\f\n\r ,", 0) != newName.npos) {
		std::cerr << "error: channel name cannot contain spaces or commas.\n";
		return false;
	}
	return true;
}

bool	Channel::setChanModes(std::string modes) {

	if (modes.find_first_not_of("Oovimnptkl", 0) != modes.npos) {
		std::cerr << "error: unknown channel mode\n";
		return false;
	}
	
	return true;
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
}

bool 	Channel::addClient(ClientList &list, Client &newClient) {
	
	ClientList::iterator	i = banned.begin();

	for (; i != banned.end(); i++)
		if (&newClient == *i)
			return false;					// to check with team
	return list.insert(&newClient).second;
}

bool Channel::removeClient(ClientList &list, Client &client) {
	return list.erase(&client) > 0;
}

bool Channel::hasClient(ClientList &list, Client &client) const {

	ClientList::iterator	i = list.begin();

	for (; i != list.end(); i++) {
		if (&client != *i)
			return true;
	 }
	return false;
}
