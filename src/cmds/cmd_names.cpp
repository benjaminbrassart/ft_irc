/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_names.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 23:54:56 by bbrassar          #+#    #+#             */
/*   Updated: 2022/12/15 02:32:08 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include "command.h"
#include "utils/NameUtils.hpp"

using NameUtils::Request;
using NameUtils::RequestList;

void cmd_names(CommandContext& ctx)
{
	Server& server = ctx.server;
	Client& client = ctx.client;
	CommandContext::ArgumentList& args = ctx.args;

	if (args.empty())
		NameUtils::showAllNames(client);
	else
	{
		CommandContext::ArgumentList chanNames = CommandContext::splitList(args[0]);
		CommandContext::ArgumentList::iterator nameIt = chanNames.begin();
		ChannelManager::iterator chanIt;
		RequestList requests;
		Request req;

		for (; nameIt != chanNames.end(); ++nameIt)
		{
			chanIt = server.channelManager.getChannel(*nameIt);
			req.name = *nameIt;
			if (chanIt == server.channelManager.end())
				req.channel = NULL;
			else
				req.channel = &*chanIt;
			requests.push_back(req);
		}

		NameUtils::showNames(client, requests);
	}

}
