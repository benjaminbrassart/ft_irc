/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 14:00:38 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/22 17:41:02 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

ChannelMode const Channel::DEFAULT_MODE = 0;

/* ==========================================================================
								COPLIEN AFORM
   ========================================================================== */

Channel::Channel() :
	server(NULL),
	mode(Channel::DEFAULT_MODE),
	name(),
	topic(),
	passwd(),
	userLimit(0),
	allClients(),
	banMasks(),
	exceptionMasks(),
	invitationMasks()
{}

Channel::Channel(Server& server, std::string name, std::string passwd) :
	server(&server),
	mode(Channel::DEFAULT_MODE),
	name(name),
	topic(),
	passwd(passwd),
	userLimit(0),
	allClients(),
	banMasks(),
	exceptionMasks(),
	invitationMasks()
{}

Channel::Channel(Channel const& rhs) :
	server(rhs.server),
	mode(rhs.mode),
	name(rhs.name),
	topic(rhs.topic),
	passwd(rhs.passwd),
	userLimit(rhs.userLimit),
	allClients(rhs.allClients),
	banMasks(rhs.banMasks),
	exceptionMasks(rhs.exceptionMasks),
	invitationMasks(rhs.invitationMasks)
{
}

Channel	&Channel::operator=(Channel const& rhs) {

	if (this != &rhs) {
		this->server = rhs.server;
		this->mode = rhs.mode;
		const_cast<std::string&>(this->name) = rhs.name;
		this->topic = rhs.topic;
		this->passwd = rhs.passwd;
		this->userLimit = rhs.userLimit;
		this->allClients = rhs.allClients;
		this->banMasks = rhs.banMasks;
		this->exceptionMasks = rhs.exceptionMasks;
		this->invitationMasks = rhs.invitationMasks;
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

bool Channel::hasClient(Client &client) const {
	return allClients.find(&client) != allClients.end();
}
