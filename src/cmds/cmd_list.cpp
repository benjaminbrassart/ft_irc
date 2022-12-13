/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 03:54:36 by bbrassar          #+#    #+#             */
/*   Updated: 2022/12/13 04:14:32 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include "command.h"

static void __list_all(Client& client);
static void __list_some(Client& client, CommandContext::ArgumentList const& names);
static void __list(Client& client, Channel& channel);

void cmd_list(CommandContext& ctx)
{
	Client& client = ctx.client;
	CommandContext::ArgumentList& args = ctx.args;

	if (args.empty())
		__list_all(client);
	else
		__list_some(client, CommandContext::splitList(args[0]));
	client.reply<RPL_LISTEND>();
}

static void __list_all(Client& client)
{
	Server& server = *client.server;
	ChannelManager::iterator chanIt = server.channelManager.begin();

	for (; chanIt != server.channelManager.end(); ++chanIt)
		__list(client, *chanIt);
}

static void __list_some(Client& client, CommandContext::ArgumentList const& names)
{
	Server& server = *client.server;
	CommandContext::ArgumentList::const_iterator nameIt = names.begin();
	ChannelManager::iterator chanIt;

	for (; nameIt != names.end(); ++nameIt)
	{
		chanIt = server.channelManager.getChannel(*nameIt);
		if (chanIt == server.channelManager.end())
			client.reply<ERR_NOSUCHCHANNEL>(*nameIt);
		else
			__list(client, *chanIt);
	}
}

static void __list(Client& client, Channel& channel)
{
	std::string const clientCount = std::string() + channel.allClients.size();

	client.reply<RPL_LIST>(channel.name, clientCount, channel.topic);
}
