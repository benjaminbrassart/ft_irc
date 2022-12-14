/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 14:00:38 by bbrassar          #+#    #+#             */
/*   Updated: 2022/12/14 17:30:36 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include <iostream>

ChannelMode const Channel::DEFAULT_MODE = 0;

/* ==========================================================================
								COPLIEN AFORM
   ========================================================================== */

Channel::Channel(Server* server) : Recipient(server),
	name(),
	topic(),
	passwd(),
	mode(Channel::DEFAULT_MODE),
	modes("+"),
	inviteMode(false),
	keyMode(false),
	usrLimitMode(false),
	userLimit(0),
	allClients(),
	allChanOps(),
	invitationMasks(),
	banMasks(),
	exceptionMasks()
{}

Channel::Channel(Server* server, std::string name, std::string passwd) : Recipient(server),
	name(name),
	topic(),
	passwd(passwd),
	mode(Channel::DEFAULT_MODE),
	modes("+"),
	inviteMode(false),
	keyMode(false),
	usrLimitMode(false),
	userLimit(0),
	allClients(),
	allChanOps(),
	invitationMasks(),
	banMasks(),
	exceptionMasks()
{}

Channel::Channel(Channel const& rhs) : Recipient(rhs.server),
	name(rhs.name),
	topic(rhs.topic),
	passwd(rhs.passwd),
	mode(rhs.mode),
	modes(rhs.modes),
	inviteMode(rhs.inviteMode),
	keyMode(rhs.keyMode),
	usrLimitMode(rhs.usrLimitMode),
	userLimit(rhs.userLimit),
	allClients(rhs.allClients),
	allChanOps(rhs.allChanOps),
	invitationMasks(rhs.invitationMasks),
	banMasks(rhs.banMasks),
	exceptionMasks(rhs.exceptionMasks)
{}

Channel	&Channel::operator=(Channel const& rhs) {

	if (this != &rhs) {
		this->server = rhs.server;
		const_cast<std::string&>(this->name) = rhs.name;
		this->topic = rhs.topic;
		this->passwd = rhs.passwd;
		this->mode = rhs.mode;
		this->modes = rhs.modes;
		this->inviteMode = rhs.inviteMode;
		this->keyMode = rhs.keyMode;
		this->usrLimitMode = rhs.usrLimitMode;
		this->userLimit = rhs.userLimit;
		this->allClients = rhs.allClients;
		this->allChanOps = rhs.allChanOps;
		this->invitationMasks = rhs.invitationMasks;
		this->banMasks = rhs.banMasks;
		this->exceptionMasks = rhs.exceptionMasks;
	}
	return (*this);
}

Channel::~Channel() {}

/* ==========================================================================
								MEMBER FUNCTIONS
   ========================================================================== */

bool Channel::empty() const
{
	return this->allClients.empty();
}

void Channel::addChanModes(std::string newModes) {

	std::string allowedModes = "ikl";

	for (uint i = 0; i < newModes.length(); i++) {
		char c = newModes[i];
		if (this->modes.find(c) == std::string::npos && allowedModes.find(c) != std::string::npos)
			this->modes += c;
	}
}

void Channel::removeChanModes(std::string byeModes) {

	std::string allowedModes = "ikl";

	for (uint i = 0; i < byeModes.length(); i++) {
		char c = byeModes[i];
		if (this->modes.find(c) == std::string::npos && allowedModes.find(c) != std::string::npos) {
			this->modes.erase(c, 1);
		}
	}
}

int	Channel::getClientPriv(Client &client) {

	int						priv = PRIV_NONE;
	ClientList::iterator 	itCli = this->allClients.begin(); 

	for (; itCli != this->allClients.end(); ++itCli)
		if (itCli->client == &client)
			priv = itCli->privilege;
	return (priv);
}

void Channel::addChanOps(std::string nick) {

	ClientList::iterator 				iteCli = this->allClients.begin(); 
	std::set< std::string >::iterator	iteChanOps = this->allChanOps.find(nick);

	for (; iteCli != this->allClients.end(); ++iteCli) {	// loop through clients
		if (iteCli->client->nickname == nick) { 		// if found with nick
			if (iteChanOps == this->allChanOps.end()) { // and it's not already in chanOps, then we add it to the list and change client's priv
				this->allChanOps.insert(nick);
				iteCli->privilege = PRIV_CHANOP;
				return ;
			}
		}
		else
			std::cerr << "error: user not found in channel.\n";
	}
}

void Channel::removeChanOps(std::string nick) {

	ClientList::iterator 				iteCli = this->allClients.begin(); 
	std::set< std::string >::iterator	iteChanOps = this->allChanOps.find(nick);

	for (; iteCli != this->allClients.end(); ++iteCli) {
		if (iteCli->client->nickname == nick) {
			if (iteChanOps == this->allChanOps.end()) {
				this->allChanOps.erase(nick);
				iteCli->privilege = PRIV_NONE;
				return ;
			}
		}
		else
			std::cerr << "error: user not found in channel.\n";
	}
}

/* ==========================================================================
								MEMBER FUNCTIONS
   ========================================================================== */

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

Channel::ClientList::iterator Channel::getClient(Client& client)
{
	ClientList::iterator it;

	for (it = this->allClients.begin(); it != this->allClients.end(); ++it)
		if (it->client == &client)
			break;
	return it;
}

std::string const& Channel::getIdentifier() const
{
	return this->name;
}

void Channel::sendMessage(Client& sender, std::string const& command, std::string const& message)
{
	std::string const& prefix = sender.asPrefix();
	ClientList::iterator it;

	for (it = this->allClients.begin(); it != this->allClients.end(); ++it)
	{
		if (it->client != &sender)
			it->client->send(prefix + " " + command + " " + this->name + " :" + message);
	}
}
