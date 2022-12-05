/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_notice.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 11:34:17 by bbrassar          #+#    #+#             */
/*   Updated: 2022/12/04 11:35:21 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include "command.h"

void cmd_notice(CommandContext& ctx)
{
	std::string const& command = ctx.name;
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
		if (recipient != NULL)
			recipient->sendMessage(client, command, args[1]);
	}
}
