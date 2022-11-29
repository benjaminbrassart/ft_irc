/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_mode.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estoffel <estoffel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 01:07:40 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/28 19:46:49 by estoffel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "Client.hpp"
// #include "ChannelMode.hpp"
// #include "command.h"
// #include <algorithm>

// enum Privilege
// {
// 	PRIV_NONE,
// 	PRIV_VOICE,
// 	PRIV_CHANOP,
// 	PRIV_UNIQOP,
// };

// enum Action
// {
// 	ENABLE,
// 	DISABLE,
// 	DISPLAY,
// };

// enum Type
// {
// 	ERROR, // invalid character
// 	ACTION, // 'enable', 'disable' or 'display'
// 	TOGGLE, // channel mode bit mask
// 	KEY, // channel password
// 	LIMIT, // channel user limit
// 	USER, // user name
// 	MASK, // ban, exception or invitation mask
// };

// union Data
// {
// 	Action action;
// 	ChannelMode toggle;
// 	struct Functions
// 	{
// 		bool (Channel::*addFunc)(std::string const&);
// 		bool (Channel::*removeFunc)(std::string const&);
// 		void (Channel::*displayFunc)(Client& client);
// 	} funcs;
// };

// struct State
// {
// 	Privilege editPrivilege;
// 	Privilege displayPrivilege;
// 	bool addRequireNext;
// 	bool removeRequireNext;
// 	Type type;
// 	Data data;
// };

// static State const STATES[256] = {};

// // TODO anonymous flag
// // https://datatracker.ietf.org/doc/html/rfc2811#section-4.2.1
// // The channel flag 'a' defines an anonymous channel.  This means that
// // when a message sent to the channel is sent by the server to users,
// // and the origin is a user, then it MUST be masked.  To mask the
// // message, the origin is changed to "anonymous!anonymous@anonymous."
// // (e.g., a user with the nickname "anonymous", the username "anonymous"
// // and from a host called "anonymous.").  Because of this, servers MUST
// // forbid users from using the nickname "anonymous".  Servers MUST also
// // NOT send QUIT messages for users leaving such channels to the other
// // channel members but generate a PART message instead.

// void cmd_mode(CommandContext& context)
// {
// 	Client&										client = context.client;
// 	std::vector< std::string > const			args = CommandContext::splitArguments(context.line);
// 	std::vector< std::string >::const_iterator	it;
// 	Channel* channel;
// 	Privilege privilege = PRIV_NONE; // TODO get it somehow

// 	if (args.empty())
// 	{
// 		client.reply<ERR_NEEDMOREPARAMS>("MODE");
// 		return;
// 	}

// 	channel = client.server->getChannel(args[0]);
// 	it = ++args.begin(); // skip channel name from arguments

// 	for (; it != args.end(); ++it)
// 	{
// 		std::string::const_iterator	sit;
// 		Action action;
// 		Privilege statePrivilege;
// 		State const* state;

// 		action = DISPLAY;

// 		for (sit = it->begin(); sit != it->end(); ++sit)
// 		{
// 			state = &STATES[static_cast<unsigned char>(*sit)];

// 			if (action == DISPLAY)
// 				statePrivilege = state->displayPrivilege;
// 			else
// 				statePrivilege = state->editPrivilege;

// 			if (privilege < statePrivilege)
// 			{
// 				if (statePrivilege == PRIV_CHANOP)
// 				{} // TODO reply with ERR_CHANOPRIVSNEEDED
// 				else
// 				{} // TODO reply with ERR_UNIQOPPRIVSNEEDED
// 				return;
// 			}

// 			if (((action == ENABLE && state->addRequireNext) ||
// 				(action == DISABLE && state->removeRequireNext)) &&
// 				++it == args.end())
// 			{
// 				client.reply<ERR_NEEDMOREPARAMS>("MODE");
// 				return;
// 			}

// 			switch (state->type)
// 			{
// 			case ACTION: // change mode (+/-)
// 				action = state->data.action;
// 				break;
// 			case KEY:
// 				channel->passwd = *it;
// 				break;
// 			case LIMIT:
// 				switch (action)
// 				{
// 				case ENABLE:
// 					channel->userLimit = 0; // TODO parse number
// 					break;
// 				case DISABLE:
// 					channel->userLimit = 0;
// 					break;
// 				case DISPLAY:
// 					break;
// 				}
// 				break;
// 			case TOGGLE:
// 				switch (action)
// 				{
// 				case ENABLE:
// 					channel->mode |= state->data.toggle;
// 					break;
// 				case DISABLE:
// 					channel->mode &= ~state->data.toggle;
// 					break;
// 				case DISPLAY:
// 					// TODO display flag to client
// 					break;
// 				}
// 				break;
// 			case MASK:
// 				switch (action)
// 				{
// 				case ENABLE:
// 					(channel->*state->data.funcs.addFunc)(*it);
// 					break;
// 				case DISABLE:
// 					(channel->*state->data.funcs.removeFunc)(*it);
// 					break;
// 				case DISPLAY:
// 					(channel->*state->data.funcs.displayFunc)(client);
// 					break;
// 				}
// 				break;
// 			case USER:
// 				// TODO find user and grant/revoke/display privilege if present in the channel
// 				break;
// 			default: // unknown type or ERROR
// 				// TODO reply with ERR_UNKNOWNMODE
// 				return;
// 			}
// 		}
// 	}
// }
