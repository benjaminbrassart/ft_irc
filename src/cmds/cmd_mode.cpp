/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_mode.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 17:18:44 by lrandria          #+#    #+#             */
/*   Updated: 2022/12/14 21:49:59 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include "ChannelMode.hpp"
#include "command.h"
#include <algorithm>
#include <iostream>

void		usrModes(Client &client, std::vector< std::string > args) {

	if (args.size() < 2) {
		client.reply<ERR_NEEDMOREPARAMS>("MODE");
		return;
	}
	if (client.nickname != args[0]) {
		client.reply<ERR_USERSDONTMATCH>();
		return;
	}
	if (args[1] == "+i")
		client.isInvisible = true;
	else if (args[1] == "-i")
		client.isInvisible = false;
	else
		client.reply<ERR_UMODEUNKNOWNFLAG>();
}

void		addModes(Client &client, ChannelManager::iterator itChan, std::vector< std::string > args) {

	if (args[1] == "+i" || args[1] == "i") {
		itChan->addChanModes("i");
		itChan->invitationMasks.insert(args[2]);
		itChan->inviteMode = true;
	}
	else if (args[1] == "+k" || args[1] == "k") {
		if (args.size() < 3) {
			client.reply<ERR_NEEDMOREPARAMS>("MODE");
			return;
		}
		itChan->addChanModes("k");
		itChan->passwd = args[2];
		itChan->keyMode = true;
	}
	else if (args[1] == "+l" || args[1] == "l") {
		if (args.size() < 3) {
			client.reply<ERR_NEEDMOREPARAMS>("MODE");
			return;
		}
		if (args[2].length() > 2 && (args[2].find('-') != std::string::npos)) 
			return ;
		itChan->userLimit = strtoul(args[2].c_str(), NULL, 10);
		if (itChan->userLimit > 0) {
			itChan->addChanModes("l");
			itChan->usrLimitMode = true;	
		}
	}
	else if ((args[1] == "+o" || args[1] == "o") && args.size() == 3) {
		if (args.size() < 3) {
			client.reply<ERR_NEEDMOREPARAMS>("MODE");
			return ;
		}
		itChan->addChanOps(args[2]);
	}
	else
		client.reply<ERR_UNKNOWNMODE>(args[1], itChan->name);
}

void		removeModes(Client &client, ChannelManager::iterator itChan, std::vector< std::string > args) {

	std::string		nick;

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
	else if (args[1] == "-o" && args.size() == 3) {
		nick = args[2];
		itChan->removeChanOps(nick);
	}
	else
		client.reply<ERR_UNKNOWNMODE>(args[1], itChan->name);
}

void	chanModes(Client &client, Server &server, std::vector< std::string > args) {

	ChannelManager::iterator			itChan;
	std::string							requestedChanName;
	std::string							modes;
	std::string							allowedChars = "iklo+";

	requestedChanName = args[0].erase(0,1);							// from #chan to chan
	itChan = server.channelManager.getChannel(requestedChanName);
	if (itChan == server.channelManager.end()) {
		client.reply<ERR_NOSUCHCHANNEL>(requestedChanName);
		return;
	}
	if (args.size() == 1) {
		client.reply<RPL_CHANNELMODEIS>(itChan->name, itChan->modes); 
		return;
	}
	else if (itChan->getClientPriv(client) < PRIV_CHANOP) { 		// is this the right check?
		client.reply<ERR_CHANOPRIVSNEEDED>(requestedChanName);
		return;
	}
	modes = args[1];
	if (modes[0] == '-' && modes.length() > 1 )
		removeModes(client, itChan, args);
	else if (allowedChars.find(modes[0]) != std::string::npos && modes.length() > 1)
		addModes(client, itChan, args);
	else
		client.reply<ERR_UNKNOWNMODE>(modes, itChan->name);
}

void	    cmd_mode(CommandContext &context) {
 
	Client							&client = context.client;
	Server							&server = context.server;	
	std::vector< std::string >		args = context.args;

	if (args.empty()) {
		client.reply<ERR_NEEDMOREPARAMS>("MODE");
		return;
	}
	else if (args[0][0] == '#')
		chanModes(client, server, args);
	else
		usrModes(client, args);
}
