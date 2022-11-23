/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_nick.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 12:31:24 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/22 23:25:51 by bbrassar         ###   ########.fr       */
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
	CommandContext::ArgumentList& args = context.args;
	std::string nickname;

	if (args.empty())
		client.reply<ERR_NONICKNAMEGIVEN>();
	else
	{
		if (!__is_nickname_valid(args[0]))
			client.reply<ERR_ERRONEUSNICKNAME>(args[0]);
		else if (!__is_nickname_available(*client.server, args[0]))
			client.reply<ERR_NICKNAMEINUSE>(args[0]);
		else
		{
			client.nickname = args[0];
			client.setState(CLIENT_STATE_NICK);
			client.tryLogin();
		}
	}
}

static bool __is_char_valid(char c)
{
	static char const SC[] = "-[]\\`_^{}|";
	static char const* const SC_BEGIN = &*&SC[0];
	static char const* const SC_END = &SC[sizeof (SC) - 1];

	return std::find(SC_BEGIN, SC_END, c) != SC_END;
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
		is_valid |= __is_char_valid(c);
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
