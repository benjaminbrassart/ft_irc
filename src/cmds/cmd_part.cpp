/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_part.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 14:11:06 by bbrassar          #+#    #+#             */
/*   Updated: 2022/12/02 15:38:07 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

#include "Client.hpp"
#include "CommandMap.hpp"
#include "Reply.hpp"

void cmd_part(CommandContext& context)
{
	Client& client = context.client;
	Server& server = context.server;
	CommandContext::ArgumentList& args = context.args;
	CommandContext::ArgumentList::const_iterator chanNameIt;
	Channel::ClientList::iterator clientIt;
	std::string const* messagePtr;

	if (args.empty())
	{
		client.reply<ERR_NEEDMOREPARAMS>(context.name);
		return;
	}

	if (args.size() < 2)
		messagePtr = &client.nickname;
	else
		messagePtr = &args[1];

	CommandContext::ArgumentList channels = CommandContext::splitList(args[0]);
	std::vector< Channel* > removedChannels;

	std::string const prefix = client.asPrefix();

	for (chanNameIt = channels.begin(); chanNameIt != channels.end(); ++chanNameIt)
	{
		Server::ChannelList::iterator chanIt = server.getChannel(*chanNameIt);

		if (chanIt == server.channels.end())
			client.reply<ERR_NOSUCHCHANNEL>(*chanNameIt);
		else if (!chanIt->hasClient(client))
			client.reply<ERR_NOTONCHANNEL>(chanIt->name);
		else
		{
			// send PART to all clients in the channel
			for (clientIt = chanIt->allClients.begin(); clientIt != chanIt->allClients.end(); ++clientIt)
				clientIt->client->send(prefix + " PART " + chanIt->name + " :" + *messagePtr);

			// remove the client from the channel
			chanIt->removeClient(client);
			client.channels.erase(&*chanIt);

			// remove the channel if no client left
			if (chanIt->allClients.empty())
				server.channels.erase(chanIt);
		}
	}
}
