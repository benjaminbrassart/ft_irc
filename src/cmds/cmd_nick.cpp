/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_nick.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 12:31:24 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/19 04:08:45 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CommandMap.hpp"
#include "Reply.hpp"
#include "Client.hpp"

#include <cctype>

#undef SPECIAL_CHARS
#define SEPCIAL_CHARS "-[]\\`_^{}|"
#define SPECIAL_CHARS_COUNT (sizeof (SPECIAL_CHARS) / sizeof (*SEPCIAL_CHARS))

/**
 * Check if a given nickname is valid
 *
 * @param nickname the nickname to check
 * @return true if nickname is valid, false otherwise
 */
static bool __is_nickname_valid(std::string const& nickname);

/**
 * Check if a given nickname has already been taken on a server
 *
 * @param server the server to retreive the logged users
 * @param nickname the nickname to check
 * @return true if the nickname is available on this server, false otherwise
 */
static bool __is_nickname_available(Server& server, std::string const& nickname);

// valid nickname characters:
// []\`_^{}|a-zZ-Z0-9-
// first character must not be a digit
// length range: 1-9
void cmd_nick(CommandContext& context)
{
	Client& client = context.client;
	std::string const& nickname = context.line;

	if (nickname.empty())
		client.reply<ERR_NONICKNAMEGIVEN>();
	else
	{
		// TODO extract nickname
		if (!__is_nickname_valid(nickname))
			client.reply<ERR_ERRONEUSNICKNAME>(nickname);
		else if (!__is_nickname_available(*client.server, nickname))
			client.reply<ERR_NICKNAMEINUSE>(nickname);
		else
		{
			client.nickname = nickname;
			client.setState(CLIENT_STATE_NICK);
			client.tryLogin();
		}
	}
}

// TODO
static bool __is_nickname_valid(std::string const& nickname)
{
	static char const SPECIAL_CHARS[] = "-[]\\`_^{}|";
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
		// TODO make this prettier
		is_valid |= (std::find(SPECIAL_CHARS, SPECIAL_CHARS + SPECIAL_CHARS_COUNT, c) != SPECIAL_CHARS + SPECIAL_CHARS_COUNT);
	}
	return is_valid;
}

static bool __is_nickname_available(Server& server, std::string const& nickname)
{
	Server::ClientList::const_iterator it;
	Client client(server);

	client.nickname = nickname;
	it = server.clients.find(client);
	return it == server.clients.end();
}
