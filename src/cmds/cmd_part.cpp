/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_part.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 14:11:06 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/25 09:20:11 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include "CommandMap.hpp"
#include "Reply.hpp"

void cmd_part(CommandContext& context)
{
	Client& client = context.client;
	Server& server = context.server;
	CommandContext::ArgumentList& args = context.args;
	CommandContext::ArgumentList::const_iterator chanNameIt;
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

	for (chanNameIt = channels.begin(); chanNameIt != channels.end(); ++chanNameIt)
	{
		Server::ChannelList::iterator chanIt = server.getChannel(*chanNameIt);

		if (chanIt == server.channels.end())
			client.reply<ERR_NOSUCHCHANNEL>(*chanNameIt);
		else if (!chanIt->hasClient(client))
			client.reply<ERR_NOTONCHANNEL>(chanIt->name);
		else
		{
			client.leaveChannel(*chanIt, *messagePtr);
			chanIt->removeClient(client);
			if (chanIt->allClients.empty())
				server.channels.erase(chanIt);
		}
	}
}
