/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_nick.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 12:31:24 by bbrassar          #+#    #+#             */
/*   Updated: 2022/12/14 01:50:46 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CommandMap.hpp"
#include "Reply.hpp"
#include "Client.hpp"

#include <cctype>

/**
 * Check if a given nickname is valid
 *
 * @param nickname the nickname to check
 * @return true if nickname is valid, false otherwise
 */
static bool __is_nickname_valid(std::string const& nickname);

// valid nickname characters:
// []\`_^{}|a-zZ-Z0-9-
// first character must not be a digit
// length range: 1-9
void cmd_nick(CommandContext& ctx)
{
	Client& client = ctx.client;
	Server& server = ctx.server;
	CommandContext::ArgumentList& args = ctx.args;

	if (args.empty())
		client.reply<ERR_NONICKNAMEGIVEN>();
	else
	{
		std::string const& nickname = args[0];

		if (!__is_nickname_valid(nickname))
			client.reply<ERR_ERRONEUSNICKNAME>(nickname);
		else if (server.nickManager.hasNickname(nickname))
			client.reply<ERR_NICKNAMEINUSE>(nickname);
		else
		{
			if (!client.checkState(CLIENT_STATE_NICK))
			{
				client.nickname = nickname;
				server.nickManager.registerNickname(nickname, &client);

				server.logger.log(DEBUG, "<" + client.address + "> Registered nickname " + nickname);
				client.setState(CLIENT_STATE_NICK);
				client.tryLogin();
			}
			else
			{
				std::set< Client* > recipients;
				std::set< Client* >::iterator recipIt;
				std::string const& prefix = client.asPrefix();
				Client::ChannelList::iterator chanIt = client.channels.begin();
				Channel::ClientList::iterator chanClientIt;

				recipients.insert(&client);
				for (; chanIt != client.channels.end(); ++chanIt)
				{
					chanClientIt = (*chanIt)->allClients.begin();

					for (; chanClientIt != (*chanIt)->allClients.end(); ++chanClientIt)
						recipients.insert(chanClientIt->client);
				}

				recipIt = recipients.begin();

				for (; recipIt != recipients.end(); ++recipIt)
					(*recipIt)->send(prefix + " NICK " + nickname);

				server.nickManager.unregisterNickname(client.nickname);

				server.logger.log(DEBUG, "<" + client.address + "> " + client.nickname + " Changed nickname to " + nickname);

				client.nickname = nickname;
				server.nickManager.registerNickname(nickname, &client);
			}
			return;
		}

		client.setState(CLIENT_STATE_NICK_FAILED);
	}
}

static bool __is_special_char(char c)
{
	switch (c)
	{
		case '-':
		case '[':
		case ']':
		case '\\':
		case '`':
		case '_':
		case '^':
		case '{':
		case '}':
		case '|':
			return true;
		default:
			return false;
	}
}

static bool __is_nickname_valid(std::string const& nickname)
{
	std::string::const_iterator it;
	std::string::value_type c;
	bool is_valid;

	is_valid = (nickname.length() <= 9);
	for (it = nickname.begin(); is_valid && it != nickname.end(); ++it)
	{
		c = *it;
		if (it == nickname.begin())
			is_valid = std::isalpha(c);
		else
			is_valid = std::isalnum(c);
		is_valid |= __is_special_char(c);
	}
	return is_valid;
}
