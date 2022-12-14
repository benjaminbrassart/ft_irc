/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_mode2.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 14:19:12 by lrandria          #+#    #+#             */
/*   Updated: 2022/12/13 15:57:06 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include "ChannelMode.hpp"
#include "command.h"
#include <iostream>
#include <algorithm>
#include <map>
#include <cstring>

// void	applyModes(std::vector< std::map<char, std::string> > modesWithParams) {


// }

// static std::string			cleanModesStr(std::string modes) {
	
// 	const int		ASCII_SIZE = 256;
// 	bool			seen[ASCII_SIZE];
// 	std::string 	output;
	
// 	for (int i = 0; i < modes.length(); i++) {
// 		if (modes[i] == '-') {
// 			while (modes[i] && modes[i] != '+') {
// 				if (modes[i] == 'i' || modes[i] == 'k' || modes[i] == 'l' ) {
// 					modes.erase(i, 1);
// 					i--;
// 				}	
// 				i++;
// 			}
// 		}
// 	}


// 	for (int i = 0; i < modes.length(); i++) {  //deleting plusses, minuses and i's
// 		if (modes[i] == '+' || modes[i] == '-' || modes[i] == 'i') {
// 			modes.erase(i, 1);
// 			i--;							 // Move back one index to make sure we don't skip any characters
// 		}
// 	}
// 	memset(seen, false, sizeof(seen));
// 	for (int i = 0; i < modes.length(); i++) {
// 		if (!seen[modes[i]]) {					// if the current character has not been seen before
// 			output += modes[i];					// append it to the output string
// 			seen[modes[i]] = true;
// 		}
// 	}
//   	return (output);
// }

// std::map<char, std::string>		assignParams(std::vector<std::string> args) {

// 	std::string							modes;	
// 	std::map<char, std::string>			result;
// 	int 								length;

// 	if (args.empty() || args[0].empty())
// 		return result;
// 	modes = cleanModesStr(args[1]);				// cleaning up modes from duplicates, '+',' -', 'i' and removals
// 	length = modes.length();
// 	if (length != args.size()) {					// maybe I can get rid of it if doesn't segfault when mismatch?
// 		std::cerr << "error: missing parameters\n";  // where can I notify it? Through a REPLY?
// 		return result;
// 	}
// 	for (int i = 0; i < length; i++) {		  // create a map with the current character as the key
// 		result[args[0][i]] = args[i + 1];		// and the corresponding string from the input vector as the value
// 				// add the map to the result vector		
// 	}
//   	return (result);
// }

// void		handleRemovingParamModes(ChannelManager::iterator iteChan, std::string &modes) {

// 	for (int i = 0; i < modes.length(); i++) {
// 		if (modes[i] == '-') {
// 			while (modes[i] != '+' && modes[i] != ' ') {
// 				if (modes[i] == 'k') {
// 					iteChan->removeChanModes("k");
// 					iteChan->keyMode = false;
// 				}
// 				i++;
// 			}
// 		}
// 		else
// 			i++;
// 	}
// }

static std::string		handle_inviteMode_KeyLimitRemoval(ChannelManager::iterator iteChan, std::string modes) {

	std::string	newStr = modes;
	size_t		pos = 0;

	for (int i = 0; i < modes.length(); i++) {
		if (modes[i] == '-') {
			while (modes[i] && modes != '+') { // 
				if (modes[i] == 'i') {
					iteChan->removeChanModes("i");
					iteChan->inviteMode = false;
					pos = 
					newStr.erase(pos, 1);
				}
				if (modes[i] == 'k') {
					iteChan->removeChanModes("k");
					iteChan->keyMode = false;
					pos = 
					newStr.erase(pos, 1);
				}
				if (modes[i] == 'l') {
					iteChan->removeChanModes("l");
					iteChan->usrLimitMode = false;
					pos = 
					newStr.erase(pos, 1);
				} 
				i++;
			}
		}
		else
			while (modes[i] && modes[i] != '-') {
				if (modes[i] == 'i') {
					iteChan->addChanModes("i");
					iteChan->inviteMode = true;
					pos = 
					newStr.erase(pos, 1);
				}
				i++;
			}
	}
	return (newStr);
}

static std::string	deleteUnknownModes(std::string modesToTrim, std::string unknownModes) {

	std::string	trimmed;

	for (int i = 0; i < modesToTrim.length(); i++) {
		char c = modesToTrim[i];
		if (unknownModes.find(c) == std::string::npos)
			trimmed += c;
	}
	return (trimmed);
}

static std::string	getUnknownModes(std::string modesToCheck) {

	std::string allowedModes = "iklao";
	std::string unknownModes;

	if (modesToCheck[0] == '+' || modesToCheck[0] == '-')
		modesToCheck = modesToCheck.erase(0,1);

	for (int i = 0; i < modesToCheck.length(); i++) {
		char c = modesToCheck[i];
		if (allowedModes.find(c) == std::string::npos)
			unknownModes += c;
	}
	return (unknownModes);
}

void	    handleModes(Client &client, Server &server, std::vector< std::string > args)
{
	ChannelManager::iterator			iteChan;
	std::string							requestedChanName;
	std::string							unknownModes;
	std::string							perfectModes;
	std::map<char, std::string>			modesWithParams;

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
	if (unknownModes) {
		client.reply<ERR_UNKNOWNMODE>(client, unknownModes, iteChan->name);
		perfectModes = deleteUnknownModes(args[1], unknownModes);
	}
	perfectModes = handle_inviteMode_KeyLimitRemoval(iteChan, perfectModes);
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
	else if (args[0][0] == '&' || args[0][0] == '#'|| args[0][0] == '+' || args[0][0] == '!')
		handleModes(client, server, args);
	else
		client.reply<ERR_NOSUCHCHANNEL>(client, args[0]);
}
