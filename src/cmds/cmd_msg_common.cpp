/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_msg_common.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 09:49:31 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/25 10:49:47 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include "command.h"

void cmd_msg_common(std::string const& command, CommandContext& ctx)
{
	Client& client = ctx.client;
	Server& server = ctx.server;
	CommandContext::ArgumentList& args = ctx.args;
	CommandContext::ArgumentList recips;
	CommandContext::ArgumentList::const_iterator recipIt;
	Recipient* recipient;

	if (args.size() < 2)
	{
		client.reply<ERR_NEEDMOREPARAMS>(command);
		return;
	}

	recips = CommandContext::splitList(args[0]);
	for (recipIt = recips.begin(); recipIt != recips.end(); ++recipIt)
	{
		recipient = server.getRecipient(*recipIt);
		if (recipient == NULL)
			client.reply<ERR_NOSUCHNICK>(*recipIt);
		else
			recipient->sendMessage(client, args[1]);
	}
}
