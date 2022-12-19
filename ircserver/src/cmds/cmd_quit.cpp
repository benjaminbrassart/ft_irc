/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_quit.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 13:50:33 by bbrassar          #+#    #+#             */
/*   Updated: 2022/12/19 18:10:57 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include "Channel.hpp"
#include "CommandMap.hpp"
#include <set>

void cmd_quit(CommandContext& ctx)
{
	CommandContext::ArgumentList& args = ctx.args;
	Client& client = ctx.client;
	Server& server = ctx.server;
	std::string const prefix = client.asPrefix();
	Client::ChannelList::iterator chanIt;
	Channel::ClientList::iterator clientIt;
	std::set< Client* > recipients;
	std::set< Client* >::iterator recipIt;
	std::string reason;

	if (!args.empty())
		reason = args[0];

	for (chanIt = client.channels.begin(); chanIt != client.channels.end(); ++chanIt)
	{
		(*chanIt)->removeClient(client);
		if ((*chanIt)->empty())
			server.channelManager.removeChannel((*chanIt)->name);
		else
			for (clientIt = (*chanIt)->allClients.begin(); clientIt != (*chanIt)->allClients.end(); ++clientIt)
				recipients.insert(clientIt->client);
	}
	for (recipIt = recipients.begin(); recipIt != recipients.end(); ++recipIt)
		(*recipIt)->send(prefix + " QUIT :Quit: " + reason);
	client.send("ERROR :buh-bye ;D");
	client.shouldClose = true;
	client.hasQuit = true;
}
