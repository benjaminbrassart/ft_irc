/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_nick.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 12:31:24 by bbrassar          #+#    #+#             */
/*   Updated: 2022/12/04 11:16:00 by bbrassar         ###   ########.fr       */
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
void cmd_nick(CommandContext& context)
{
	Client& client = context.client;
	Server& server = context.server;
	CommandContext::ArgumentList& args = context.args;

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
				server.logger.log(DEBUG, "<" + client.address + "> Registered nickname " + nickname);
				client.setState(CLIENT_STATE_NICK);
				client.tryLogin();
			}
			else
				server.logger.log(DEBUG, "<" + client.address + "> " + client.nickname + " Changed nickname to " + nickname);
			client.nickname = nickname;
			server.nickManager.registerNickname(nickname, &client);
		}
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
