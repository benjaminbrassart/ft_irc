/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_join.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 19:11:58 by bbrassar          #+#    #+#             */
/*   Updated: 2022/12/04 14:41:14 by bbrassar         ###   ########.fr       */
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
	std::vector< std::string > channels;
	std::vector< std::string > keys;
	std::vector< std::string >::const_iterator chanNameIt;
	std::vector< std::string >::const_iterator keyIt;
	Channel::ClientList::iterator clientIt;

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

	std::string const prefix = client.asPrefix();

	channels = CommandContext::splitList(args[0]);
	if (args.size() < 2)
		keys = CommandContext::ArgumentList();
	else
		keys = CommandContext::splitList(args[1]);

	chanNameIt = channels.begin();
	keyIt = keys.begin();

	for (; chanNameIt != channels.end(); ++chanNameIt)
	{
		ChannelManager::iterator chanIt = server.channelManager.getChannel(*chanNameIt);
		ChannelPrivilege priv;

		if (chanIt == server.channelManager.end())
		{
			chanIt = server.channelManager.addChannel(Channel(&server, *chanNameIt));
			priv = PRIV_UNIQOP;
		}
		else
			priv = PRIV_NONE;

		std::string key;

		if (keyIt != keys.end())
			key = *keyIt++;

		if (key.empty() || chanIt->passwd == key)
		{
			chanIt->addClient(client, priv);

			for (clientIt = chanIt->allClients.begin(); clientIt != chanIt->allClients.end(); ++clientIt)
			{
				clientIt->client->send(prefix + " JOIN " + chanIt->name);
				client.reply<RPL_NAMREPLY>();
			}
			client.reply<RPL_ENDOFNAMES>(chanIt->name);
			client.reply<RPL_TOPIC>(chanIt->name, chanIt->topic);
		}
		else
			client.reply<ERR_PASSWDMISMATCH>();
	}
}
