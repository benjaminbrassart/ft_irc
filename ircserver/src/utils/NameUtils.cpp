/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NameUtils.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 01:55:43 by bbrassar          #+#    #+#             */
/*   Updated: 2022/12/16 01:03:40 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/NameUtils.hpp"

static void __showClient(Client& sender, Channel::ClientList::iterator const& it, Channel& channel, bool isMember);

void NameUtils::showAllNames(Client& client)
{
	Server& server = *client.server;
	ChannelManager::iterator it = server.channelManager.begin();
	RequestList reqs;
	Request req;

	for (; it != server.channelManager.end(); ++it)
	{
		req.name = it->name;
		req.channel = &*it;
		reqs.push_back(req);
	}

	showNames(client, reqs);
}

void NameUtils::showNames(Client& client, RequestList& requests)
{
	RequestList::iterator it = requests.begin();

	for (; it != requests.end(); ++it)
		showName(client, *it);
}

void NameUtils::showName(Client& client, Request& request)
{
	std::string const* namePtr = &request.name;
	Channel::ClientList::iterator clientIt;

	if (request.channel != NULL)
	{
		Channel& channel = *request.channel;
		bool isMember = channel.hasClient(client);

		if (isMember)
		{
			namePtr = &channel.name;
			clientIt = channel.allClients.begin();
			for (; clientIt != channel.allClients.end(); ++clientIt)
				__showClient(client, clientIt, channel, isMember);
		}
	}

	client.reply<RPL_ENDOFNAMES>(*namePtr);
}

static void __showClient(Client& sender, Channel::ClientList::iterator const& it, Channel& channel, bool isMember)
{
	Client& client = *it->client;
	std::stringstream ss;

	if (isMember || !client.isInvisible)
	{
		switch (it->privilege)
		{
			case PRIV_UNIQOP:
			case PRIV_CHANOP: ss << '@'; break;
			case PRIV_VOICE:  ss << '+'; break;
			default: break;
		}

		std::string symbol = "=";

		ss << it->client->nickname;
		sender.reply<RPL_NAMREPLY>(symbol, channel.name, ss.str());
	}
}
