/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 14:00:38 by bbrassar          #+#    #+#             */
/*   Updated: 2022/12/02 15:36:06 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include <iostream>

ChannelMode const Channel::DEFAULT_MODE = 0;

/* ==========================================================================
								COPLIEN AFORM
   ========================================================================== */

Channel::Channel(Server& server) : Recipient(server),
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

Channel::Channel(Server& server, std::string name, std::string passwd) : Recipient(server),
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

Channel::Channel(Channel const& rhs) : Recipient(*rhs.server),
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
	(void)sender;
	(void)msg;

	// TODO
}

void	Channel::addClient(Client &client, ChannelPrivilege privilege) {
	ClientPrivilege const entry = {&client, privilege};

	this->allClients.push_back(entry);
}

void Channel::removeClient(Client &client) {
	ClientList::iterator it;

	for (it = this->allClients.begin(); it != this->allClients.end(); ++it)
		if (it->client == &client)
		{
			this->allClients.erase(it);
			return;
		}
}

bool Channel::hasClient(Client &client) const {
	ClientList::const_iterator it;

	for (it = this->allClients.begin(); it != this->allClients.end(); ++it)
		if (it->client == &client)
			return true;
	return false;
}

std::string const& Channel::getIdentifier() const
{
	return this->name;
}

void Channel::sendMessage(Client& sender, std::string const& message)
{
	ClientList::iterator it;

	for (it = this->allClients.begin(); it != this->allClients.end(); ++it)
	{
		if (&sender != it->client)
			it->client->sendMessage(sender, message);
	}
}
