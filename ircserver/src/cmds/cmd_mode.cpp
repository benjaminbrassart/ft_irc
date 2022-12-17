/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_mode.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 17:18:44 by lrandria          #+#    #+#             */
/*   Updated: 2022/12/17 07:03:35 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include "command.h"
#include <algorithm>
#include <iostream>

void		usrModes(Client &client, std::vector< std::string >& args) {

	if (client.nickname != args[0]) {
		client.reply<ERR_USERSDONTMATCH>();
		return;
	}
	if (args.size() == 1) {

		std::string	clientModes = "+";

		if (client.isInvisible == true)
			clientModes += 'i';
		if (client.checkState(CLIENT_STATE_OPERATOR))
			clientModes += 'o';
		client.reply<RPL_UMODEIS>(clientModes);
		return;
	}
	if (args[1] == "+i")
		client.isInvisible = true;
	else if (args[1] == "-i")
		client.isInvisible = false;
	else
		client.reply<ERR_UMODEUNKNOWNFLAG>();
}

bool		addModes(Client &client, ChannelManager::iterator itChan, std::vector< std::string >& args) {

	NicknameManager::iterator		itNick;
	Channel::ClientList::iterator 	itClient;

	if (args[1] == "+i" || args[1] == "i") {
		itChan->addChanModes("i");
		if (itChan->inviteMode == true)
			return false;
		itChan->inviteMode = true;
		for (itClient = itChan->allClients.begin(); itClient != itChan->allClients.end(); ++itClient)
			itClient->client->send("MODE " +  itChan->name + " " + args[1]);
		return true;
	}
	else if (args[1] == "+k" || args[1] == "k") {
		if (args.size() < 3) {
			client.reply<ERR_NEEDMOREPARAMS>("MODE");
			return false;
		}
		itChan->addChanModes("k");
		itChan->passwd = args[2];
		if (itChan->keyMode == true)
			return false;
		itChan->keyMode = true;
	}
	else if (args[1] == "+l" || args[1] == "l") {
		if (args.size() < 3) {
			client.reply<ERR_NEEDMOREPARAMS>("MODE");
			return false;
		}
		if (args[2].length() > 2 && (args[2].find('-') != std::string::npos))
			return false;
		itChan->userLimit = strtoul(args[2].c_str(), NULL, 10);
		if (itChan->userLimit > 0) {
			itChan->addChanModes("l");
			if (itChan->usrLimitMode == true)
				return false;
			itChan->usrLimitMode = true;
		}
	}
	else if ((args[1] == "+o" || args[1] == "o")) {
		if (args.size() < 3) {
			client.reply<ERR_NEEDMOREPARAMS>("MODE");
			return false;
		}
		itNick = client.server->nickManager.getClient(args[2]);
		if (itNick == client.server->nickManager.end())
		{
			client.reply<ERR_USERNOTINCHANNEL>(args[2], itChan->name);
			return false;
		}
		itChan->setPriv(args[2], PRIV_CHANOP);
	}
	else {
		client.reply<ERR_UNKNOWNMODE>(args[1], itChan->name);
		return false;
	}
	for (itClient = itChan->allClients.begin(); itClient != itChan->allClients.end(); ++itClient)
		itClient->client->send("MODE " +  itChan->name + " " + args[1] + " " + args[2]);
	return true;
}

bool	removeModes(Client &client, ChannelManager::iterator itChan, std::vector< std::string >& args) {

	NicknameManager::iterator	itNick;
	Channel::ClientList::iterator 	itClient;

	if (args[1] == "-i") {
		itChan->removeChanModes("i");
		itChan->inviteMode = false;
	}
	else if (args[1] == "-k") {
		itChan->removeChanModes("k");
		itChan->keyMode = false;
	}
	else if (args[1] == "-l") {
		itChan->removeChanModes("l");
		itChan->usrLimitMode = false;
	}
	else if (args[1] == "-o") {
		if (args.size() < 3) {
			client.reply<ERR_NEEDMOREPARAMS>("MODE");
			return false;
		}
		itNick = client.server->nickManager.getClient(args[2]);
		if (itNick == client.server->nickManager.end())
		{
			client.reply<ERR_NOTONCHANNEL>(itChan->name);
			return false;
		}
		itChan->setPriv(args[2], PRIV_NONE);
	}
	else {
		client.reply<ERR_UNKNOWNMODE>(args[1], itChan->name);
		return false;
	}
	for (itClient = itChan->allClients.begin(); itClient != itChan->allClients.end(); ++itClient)
		itClient->client->send("MODE " +  itChan->name + " " + args[1]);
	return true;
}

void	chanModes(Client &client, Server &server, std::vector< std::string >& args) {

	ChannelManager::iterator			itChan;
	Channel::ClientList::iterator		itCli;
	std::string							modes;
	std::string							allowedChars = "iklo+";
	bool								updated = false;

	itChan = server.channelManager.getChannel(args[0]);
	if (itChan == server.channelManager.end()) {
		client.reply<ERR_NOSUCHCHANNEL>(args[0]);
		return;
	}
	if (args.size() == 1) {
		client.reply<RPL_CHANNELMODEIS>(itChan->name, itChan->modes);
		return;
	}
	else if (itChan->getClientPriv(client) < PRIV_CHANOP) {
		client.reply<ERR_CHANOPRIVSNEEDED>(args[0]);
		return;
	}
	modes = args[1];
	if (modes[0] == '-' && modes.length() > 1 )
		updated = removeModes(client, itChan, args);
	else if (allowedChars.find(modes[0]) != std::string::npos && modes.length() > 1)
		updated = addModes(client, itChan, args);
	else {
		client.reply<ERR_UNKNOWNMODE>(modes, itChan->name);
		return;
	}
	if (updated) {

		std::string const prefix = client.asPrefix();

		for (itCli = itChan->allClients.begin(); itCli != itChan->allClients.end(); ++itCli)
			itCli->client->send(prefix + " MODE " + itChan->name + " " + modes);
	}
}

void		cmd_mode(CommandContext &ctx) {

	Client							&client = ctx.client;
	Server							&server = ctx.server;
	std::vector< std::string >		&args = ctx.args;

	if (args.empty()) {
		client.reply<ERR_NEEDMOREPARAMS>(ctx.name);
		return;
	}
	else if (args[0][0] == '#')
		chanModes(client, server, args);
	else
		usrModes(client, args);
}
