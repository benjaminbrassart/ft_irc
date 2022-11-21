/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 14:00:38 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/21 03:34:24 by bbrassar         ###   ########.fr       */
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
		this->name = rhs.name;
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
