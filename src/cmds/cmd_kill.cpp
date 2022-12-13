/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_kill.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 03:00:42 by bbrassar          #+#    #+#             */
/*   Updated: 2022/12/13 20:59:50 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "Client.hpp"
#include "Channel.hpp"

void cmd_kill(CommandContext& ctx)
{
	CommandContext::ArgumentList& args = ctx.args;
	Client& client = ctx.client;
	Server& server = ctx.server;
	std::set< Client* > contents;
	std::set< Client* >::iterator contentIt;

	if (args.size() < 2)
		client.reply<ERR_NEEDMOREPARAMS>(ctx.name);
	else if (!client.checkState(CLIENT_STATE_OPERATOR))
		client.reply<ERR_NOPRIVILEGES>();
	else
	{
		std::string reason = args[1];
		NicknameManager::iterator ClientIt = server.nickManager.getClient(args[0]);
		if (ClientIt == server.nickManager.end())
			return ;
		std::string const prefix = ClientIt->second->asPrefix();
		Client::ChannelList::iterator ChanIt = ClientIt->second->channels.begin();
		for (; ChanIt != ClientIt->second->channels.end(); ++ChanIt) {
			Channel::ClientList::iterator ChanClientIt = (*ChanIt)->allClients.begin();
			for (; ChanClientIt != (*ChanIt)->allClients.end(); ++ChanClientIt)
				contents.insert(ChanClientIt->client);
		}
		for (contentIt = contents.begin(); contentIt != contents.end(); ++contentIt)
			(*contentIt)->send(prefix + " KILL :Killed: by " + client.nickname + reason);
		ClientIt->second->send("ERROR :buh-bye loser");
		ClientIt->second->shouldClose = true;
	}
}
