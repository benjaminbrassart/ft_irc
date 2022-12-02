/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_join.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 19:11:58 by bbrassar          #+#    #+#             */
/*   Updated: 2022/12/02 16:21:19 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include "command.h"

// Once a user has joined a channel, he receives information about
// all commands his server receives affecting the channel.  This
// includes JOIN, MODE, KICK, PART, QUIT and of course PRIVMSG/NOTICE.
// This allows channel members to keep track of the other channel
// members, as well as channel modes.

// If a JOIN is successful, the user receives a JOIN message as
// confirmation and is then sent the channel's topic (using RPL_TOPIC) and
// the list of users who are on the channel (using RPL_NAMREPLY), which
// MUST include the user joining.

void cmd_join(CommandContext& context)
{
	Client& client = context.client;
	Server& server = context.server;
	CommandContext::ArgumentList& args = context.args;
	std::vector < std::string > channels;
	std::vector < std::string > keys;
	std::vector < std::string >::const_iterator chanNameIt;
	std::vector < std::string >::const_iterator keyIt;

	if (args.empty())
	{
		client.reply<ERR_NEEDMOREPARAMS>(context.name);
		return;
	}

	if (args[0] == "0")
	{
		// TODO loop through channels, remove client and clear client's channels
		return;
	}

	channels = CommandContext::splitList(args[0]);
	if (args.size() < 2)
		keys = CommandContext::ArgumentList();
	else
		keys = CommandContext::splitList(args[1]);

	chanNameIt = channels.begin();
	keyIt = keys.begin();

	for (; chanNameIt != channels.end(); ++chanNameIt)
	{
		Server::ChannelList::iterator chanIt = server.getChannel(*chanNameIt);
		Channel* chanPtr;
		ChannelPrivilege priv;

		if (chanIt == server.channels.end())
		{
			server.channels.push_back(Channel(&server, *chanNameIt));
			chanPtr = &server.channels.back();
			priv = PRIV_UNIQOP;
		}
		else
		{
			chanPtr = &*chanIt;
			priv = PRIV_NONE;
		}

		Channel& chan = *chanPtr;
		std::string key;

		if (keyIt != keys.end())
			key = *keyIt++;

		if (key.empty() || chan.passwd == key)
		{
			chan.addClient(client, priv);
			// TODO loop throught clients and send JOIN
		}
		else
			client.reply<ERR_PASSWDMISMATCH>();
	}
}
