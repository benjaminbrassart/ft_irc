/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_kick.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 04:23:21 by bbrassar          #+#    #+#             */
/*   Updated: 2022/12/13 04:48:48 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include "command.h"

// the server should use a default message if none is supplied
#define DEFAULT_REASON "Smell ya later"

void cmd_kick(CommandContext& ctx)
{
	Server& server = ctx.server;
	Client& client = ctx.client;
	CommandContext::ArgumentList& args = ctx.args;

	// need at least 2 parameters
	if (args.size() < 2)
	{
		client.reply<ERR_NEEDMOREPARAMS>(ctx.name);
		return;
	}

	ChannelManager::iterator chanIt = server.channelManager.getChannel(args[0]);

	// channel does not exist
	if (chanIt == server.channelManager.end())
	{
		client.reply<ERR_NOSUCHCHANNEL>(ctx.name);
		return;
	}

	Channel::ClientList::iterator cliPrivIt = chanIt->getClient(client);

	// the sender is not in the requested channel
	if (cliPrivIt == chanIt->allClients.end())
	{
		client.reply<ERR_NOTONCHANNEL>(chanIt->name);
		return;
	}

	// the sender is not at least channel operator
	if (cliPrivIt->privilege < PRIV_CHANOP)
	{
		client.reply<ERR_CHANOPRIVSNEEDED>(chanIt->name);
		return;
	}

	std::string const prefix = client.asPrefix();
	std::string const reason = (args.size() >= 3) ? args[2] : DEFAULT_REASON;
	CommandContext::ArgumentList names = CommandContext::splitList(args[1]);
	CommandContext::ArgumentList::iterator nameIt = names.begin();
	NicknameManager::iterator clientIt;
	Channel::ClientList::iterator clientMemberIt;

	// loop through client names
	for (; nameIt != names.end(); ++nameIt)
	{
		clientIt = server.nickManager.getClient(*nameIt);
		// check if the client exists

		if (clientIt != server.nickManager.end())
		{
			cliPrivIt = chanIt->getClient(*clientIt->second);
			// check if the client is in the channel

			if (cliPrivIt != chanIt->allClients.end())
			{
				clientMemberIt = chanIt->allClients.begin();

				// send KICK to all clients in the channel
				for (; clientMemberIt != chanIt->allClients.end(); ++clientMemberIt)
					clientMemberIt->client->send(prefix + " KICK " + chanIt->name + " " + clientIt->second->nickname + " :" + reason);
				chanIt->removeClient(*cliPrivIt->client);
				continue;
			}
		}
		client.reply<ERR_USERNOTINCHANNEL>(*nameIt, chanIt->name);
	}

	// delete the channel if it is empty (possible if the only client in the channel kicks itself)
	if (chanIt->empty())
		server.channelManager.removeChannel(chanIt);
}
