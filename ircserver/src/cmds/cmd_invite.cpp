/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_invite.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 16:40:38 by lrandria          #+#    #+#             */
/*   Updated: 2022/12/19 14:52:13 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "Client.hpp"
#include "Channel.hpp"

void cmd_invite(CommandContext& ctx)
{
	Client							&client = ctx.client;
	Server							&server = ctx.server;
	std::vector< std::string >&		args = ctx.args;
	ChannelManager::iterator		itChan;
    NicknameManager::iterator		itNick;

	if (args.size() < 2) {
		client.reply<ERR_NEEDMOREPARAMS>(ctx.name);
        return;
    }

    itChan = server.channelManager.getChannel(args[1]);

	if (itChan == server.channelManager.end()) {
		client.reply<ERR_NOSUCHCHANNEL>(args[1]);
		return;
	}

	Channel::ClientList::iterator chanClientIt = itChan->getClient(client);

	if (chanClientIt == itChan->allClients.end())
	{
		client.reply<ERR_NOTONCHANNEL>(itChan->name);
		return;
	}

	if (chanClientIt->privilege < PRIV_CHANOP) {
		client.reply<ERR_CHANOPRIVSNEEDED>(itChan->name);
		return;
	}

	itNick = server.nickManager.getClient(args[0]);

	if (itNick == server.nickManager.end())
	{
		client.reply<ERR_NOSUCHNICK>(args[0]);
		return;
	}

	Channel::ClientList::iterator clientIt = itChan->getClient(*itNick->second);

	if (clientIt != itChan->allClients.end())
	{
		client.reply<ERR_USERONCHANNEL>(itNick->second->nickname, itChan->name);
		return;
	}

	client.reply<RPL_INVITING>(itNick->second->nickname, itChan->name);

	std::string const prefix = client.asPrefix();

	itNick->second->send(prefix + " INVITE " + itNick->second->nickname + " " + itChan->name);
	itChan->inviteClient(*itNick->second);
}
