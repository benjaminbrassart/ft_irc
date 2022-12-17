/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_join.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 19:11:58 by bbrassar          #+#    #+#             */
/*   Updated: 2022/12/16 19:39:43 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include "command.h"
#include "utils/NameUtils.hpp"

static bool __check_channel_name(std::string const& name);

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
		if (!__check_channel_name(*chanNameIt))
		{
			client.reply<ERR_BADCHANMASK>(*chanNameIt);
			continue;
		}

		ChannelManager::iterator chanIt = server.channelManager.getChannel(*chanNameIt);
		ChannelPrivilege priv;

		if (chanIt == server.channelManager.end())
		{
			chanIt = server.channelManager.addChannel(Channel(&server, *chanNameIt));
			priv = PRIV_UNIQOP;
		}
		else
		{
			if (chanIt->hasClient(client))
				continue;
			if (chanIt->inviteMode && !chanIt->isInvited(client))
			{
				client.reply<ERR_INVITEONLYCHAN>(chanIt->name);
				continue;
			}
			chanIt->uninviteClient(client);
			priv = PRIV_NONE;
		}

		std::string key;

		if (keyIt != keys.end())
			key = *keyIt++;

		if (chanIt->keyMode && key != chanIt->passwd)
		{
			client.reply<ERR_BADCHANNELKEY>(chanIt->name);
			continue;
		}

		client.channels.insert(&*chanIt);
		chanIt->addClient(client, priv);

		if (!chanIt->topic.empty())
			client.reply<RPL_TOPIC>(chanIt->name, chanIt->topic);

		for (clientIt = chanIt->allClients.begin(); clientIt != chanIt->allClients.end(); ++clientIt)
		{
			std::stringstream ss;

			clientIt->client->send(prefix + " JOIN " + chanIt->name);

			switch (clientIt->privilege)
			{
				case PRIV_UNIQOP:
				case PRIV_CHANOP: ss << '@'; break;
				case PRIV_VOICE: ss << '+'; break;
				default: break;
			}

			std::string symbol = "=";

			ss << clientIt->client->nickname;
			client.reply<RPL_NAMREPLY>(symbol, chanIt->name, ss.str());
		}
		client.reply<RPL_ENDOFNAMES>(chanIt->name);
	}
}

static bool __check_channel_name(std::string const& name)
{
	if (name.empty() || name.size() > 50 || name[0] != '#')
		return false;
	return name.find_first_of("\b\r\n ,:") == std::string::npos;
}
