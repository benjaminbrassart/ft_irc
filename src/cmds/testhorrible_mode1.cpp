/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_mode.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 14:19:12 by lrandria          #+#    #+#             */
/*   Updated: 2022/12/13 14:08:10 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include "ChannelMode.hpp"
#include "command.h"
#include <iostream>
#include <algorithm>
#include <map>
#include <cstring>

void	applyModes(std::vector< std::map<char, std::string> > modesWithParams) {


}

static std::string			cleanModesStr(std::string modes) {
	
	const int		ASCII_SIZE = 256;
	bool			seen[ASCII_SIZE];
	std::string 	output;
	
	for (int i = 0; i < modes.length(); i++) {
		if (modes[i] == '-') {
			while (modes[i] && modes[i] != '+') {
				if (modes[i] == 'i' || modes[i] == 'k' || modes[i] == 'l' ) {
					modes.erase(i, 1);
					i--;
				}	
				i++;
			}
		}
	}


	for (int i = 0; i < modes.length(); i++) {  //deleting plusses, minuses and i's
		if (modes[i] == '+' || modes[i] == '-' || modes[i] == 'i') {
			modes.erase(i, 1);
			i--;							 // Move back one index to make sure we don't skip any characters
		}
	}
	memset(seen, false, sizeof(seen));
	for (int i = 0; i < modes.length(); i++) {
		if (!seen[modes[i]]) {					// if the current character has not been seen before
			output += modes[i];					// append it to the output string
			seen[modes[i]] = true;
		}
	}
  	return (output);
}

std::map<char, std::string>		assignParams(std::vector<std::string> args) {

	std::string							modes;	
	std::map<char, std::string>			result;
	int 								length;

	if (args.empty() || args[0].empty())
		return result;
	modes = cleanModesStr(args[1]);				// cleaning up modes from duplicates, '+',' -', 'i' and removals
	length = modes.length();
	if (length != args.size()) {					// maybe I can get rid of it if doesn't segfault when mismatch?
		std::cerr << "error: missing parameters\n";  // where can I notify it? Through a REPLY?
		return result;
	}
	for (int i = 0; i < length; i++) {		  // create a map with the current character as the key
		result[args[0][i]] = args[i + 1];		// and the corresponding string from the input vector as the value
				// add the map to the result vector		
	}
  	return (result);
}

void		handleRemovingParamModes(ChannelManager::iterator iteChan, std::string &modes) {

	for (int i = 0; i < modes.length(); i++) {
		if (modes[i] == '-') {
			while (modes[i] != '+' && modes[i] != ' ') {
				if (modes[i] == 'k') {
					iteChan->removeChanModes("k");
					iteChan->keyMode = false;
				}
				i++;
			}
		}
		else
			i++;
	}
}

void		handle_inviteMode_KeyLimitRemoval(ChannelManager::iterator iteChan, std::string modes) {

	for (int i = 0; i < modes.length(); i++) {
		if (modes[i] == '-') {
			while (modes[i] != '+' && modes[i] != ' ') { // 
				if (modes[i] == 'i') {
					iteChan->removeChanModes("i");
					iteChan->inviteMode = false;
				}
				if (modes[i] == 'k') {
					iteChan->removeChanModes("k");
					iteChan->keyMode = false;
				}
				if (modes[i] == 'l') {
					iteChan->removeChanModes("k");
					iteChan->usrLimitMode = false;
				} 
				i++;
			}
		}
		else
			while (modes[i] != '-' && modes[i] != ' ') {
				if (modes[i] == 'i') {
					iteChan->addChanModes("i");
					iteChan->inviteMode = true;
				}
				i++;
			}
	}
}

void	    handleModes(Client &client, Server &server, std::vector< std::string > args)
{
	std::string							requestedChanName;
	ChannelManager::iterator			iteChan;
	std::map<char, std::string>			modesWithParams;
	std::string							unknownModes;
	std::string							perfectModes;

	requestedChanName = args[0].erase(0,1);								// from #chan to chan
	iteChan = server.channelManager.getChannel(requestedChanName);
	if (iteChan == server.channelManager.end()) {
		client.reply<ERR_NOSUCHCHANNEL>(requestedChanName);
		return;
	}
	if (args.size() == 1) {
		client.reply<RPL_CHANNELMODEIS>(iteChan->name, iteChan->modes); 
		// client.reply<RPL_CREATED>() maybe add date of creation?
		return;
	}
	else if (!client.checkState(CLIENT_STATE_OPERATOR)) { // is this the right check?
		client.reply<ERR_CHANOPRIVSNEEDED>(requestedChanName);
		return;
	}
	unknownModes = getUnknownModes(args[1]);
	handle_inviteMode_KeyLimitRemoval(iteChan, args[1]);
	handleRemoving_KeyLimitModes(iteChan, args[1]);
	modesWithParams = assignParams(args);
	applyModes(modesWithParams);
}

void	    cmd_mode(CommandContext &context) {
 
	Client							&client = context.client;
	Server							&server = context.server;	
	std::vector< std::string >		args = context.args;

	if (args.empty()) {
		client.reply<ERR_NEEDMOREPARAMS>("MODE");
		return;
	}
	else if (args[0][0] == '#') // maybe add other channels prefixes?
		handleModes(client, server, args);
	else
		client.reply<ERR_NOSUCHCHANNEL>(client, args[0]); // Why is this not working? How come it's not the right args?
}
