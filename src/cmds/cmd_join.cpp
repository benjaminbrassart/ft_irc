/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_join.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 19:11:58 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/22 23:28:47 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include "command.h"

// Once a user has joined a channel, he receives information about
// all commands his server receives affecting the channel.  This
// includes JOIN, MODE, KICK, PART, QUIT and of course PRIVMSG/NOTICE.
// This allows channel members to keep track of the other channel
// members, as well as channel modes.

// If a JOIN is successful, the user receives a JOIN message as
// confirmation and is then sent the channel's topic (using RPL_TOPIC) and
// the list of users who are on the channel (using RPL_NAMREPLY), which
// MUST include the user joining.

void cmd_join(CommandContext& context)
{
	Client& client = context.client;
	Server& server = context.server;
	CommandContext::ArgumentList& args = context.args;
	std::vector < std::string > channels;
	std::vector < std::string > keys;
	std::vector < std::string >::const_iterator chan_it;
	std::vector < std::string >::const_iterator key_it;

	if (args.empty())
	{
		client.reply<ERR_NEEDMOREPARAMS>("JOIN");
		return;
	}

	if (args[0] == "0")
	{
		client.leaveAllChannels(""); // TODO
		return;
	}

	channels = CommandContext::split(args[0], ',');
	keys = CommandContext::split(args[1], ',');

	chan_it = channels.begin();
	key_it = keys.begin();

	for (; chan_it != channels.end(); ++chan_it)
	{
		Channel& chan = server.getOrCreateChannel(*chan_it);
		std::string key;

		if (key_it != keys.end())
			key = *key_it++;

		if (chan.passwd == key)
		{
			// client.joinChanel(chan); // TODO
			chan.addClient(client);
		}
		else
			client.reply<ERR_PASSWDMISMATCH>();
	}
}
