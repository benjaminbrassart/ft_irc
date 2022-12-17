/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_topic.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 16:05:40 by bbrassar          #+#    #+#             */
/*   Updated: 2022/12/14 23:14:11 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "Client.hpp"

static void __send_topic(Channel& channel, Client& client);
static void __set_topic(Channel& channel, Client& client, ChannelPrivilege priv, std::string const& topic);

void cmd_topic(CommandContext& ctx)
{
	CommandContext::ArgumentList& args = ctx.args;
	Client& client = ctx.client;
	Server& server = ctx.server;

	// not enough arguments
	if (args.empty())
	{
		client.reply<ERR_NEEDMOREPARAMS>(ctx.name);
		return;
	}

	ChannelManager::iterator chanIt = server.channelManager.getChannel(args[0]);

	// channel with such name not found
	if (chanIt == server.channelManager.end())
	{
		client.reply<ERR_NOSUCHCHANNEL>(args[0]);
		return;
	}

	Channel::ClientList::iterator clientIt = chanIt->getClient(client);

	// client is not on channel
	if (clientIt == chanIt->allClients.end())
	{
		client.reply<ERR_NOTONCHANNEL>(chanIt->name);
		return;
	}

	if (args.size() == 1)
		__send_topic(*chanIt, client);
	else
		__set_topic(*chanIt, client, clientIt->privilege, args[1]);
}

static void __send_topic(Channel& channel, Client& client)
{
	if (channel.topic.empty())
		client.reply<RPL_NOTOPIC>(channel.name);
	else
		client.reply<RPL_TOPIC>(channel.name, channel.topic);
}

static void __set_topic(Channel& channel, Client& client, ChannelPrivilege priv, std::string const& topic)
{
	if (priv < PRIV_CHANOP)
		client.reply<ERR_CHANOPRIVSNEEDED>(channel.name);
	else
	{
		std::string prefix = client.asPrefix();

		channel.topic = topic;
		for (Channel::ClientList::iterator it = channel.allClients.begin(); it != channel.allClients.end(); ++it)
			it->client->send(prefix + " TOPIC " + channel.name + " :" + channel.topic);
	}
}
