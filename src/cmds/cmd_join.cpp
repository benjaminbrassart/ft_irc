/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_join.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 19:11:58 by bbrassar          #+#    #+#             */
/*   Updated: 2022/12/13 20:59:50 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include "command.h"

static bool __check_channel_name(std::string const& name);

// Once a user has joined a channel, he receives information about
// all commands his server receives affecting the channel.  This
// includes JOIN, MODE, KICK, PART, QUIT and of course PRIVMSG/NOTICE.
// This allows channel members to keep track of the other channel
// members, as well as channel modes.

// If a JOIN is successful, the user receives a JOIN message as
// confirmation and is then sent the channel's topic (using RPL_TOPIC) and
// the list of users who are on the channel (using RPL_NAMREPLY), which
// MUST include the user joining.

void cmd_join(CommandContext& ctx)
{
	Client& client = ctx.client;
	Server& server = ctx.server;
	CommandContext::ArgumentList& args = ctx.args;
	std::vector< std::string > channels;
	std::vector< std::string > keys;
	std::vector< std::string >::const_iterator chanNameIt;
	std::vector< std::string >::const_iterator keyIt;
	Channel::ClientList::iterator clientIt;

	if (args.empty())
	{
		client.reply<ERR_NEEDMOREPARAMS>(ctx.name);
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

		if (!__check_channel_name(*chanNameIt))
		{
			client.reply<ERR_BADCHANMASK>(*chanNameIt);
			continue;
		}

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
			client.channels.insert(&*chanIt);
			chanIt->addClient(client, priv);

			if (chanIt->topic.empty())
				client.reply<RPL_NOTOPIC>(chanIt->name);
			else
				client.reply<RPL_TOPIC>(chanIt->name, chanIt->topic);

			for (clientIt = chanIt->allClients.begin(); clientIt != chanIt->allClients.end(); ++clientIt)
			{
				std::stringstream clientList;

				clientIt->client->send(prefix + " JOIN " + chanIt->name);

				switch (clientIt->privilege)
				{
					case PRIV_UNIQOP:
					case PRIV_CHANOP: clientList << '@'; break;
					case PRIV_VOICE: clientList << '+'; break;
					default: break;
				}
				clientList << clientIt->client->nickname;
				client.reply<RPL_NAMREPLY>("=", chanIt->name, clientList.str());
			}
			// TOOD see if we need to split this if there are too many clients
			client.reply<RPL_ENDOFNAMES>(chanIt->name);
		}
		else
			client.reply<ERR_PASSWDMISMATCH>();
	}
}

static bool __check_channel_name(std::string const& name)
{
	if (name.empty() || name.size() > 50 || name[0] != '#')
		return false;
	// TODO check for forbidden characters
	return true;
}
