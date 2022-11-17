/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_nick.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 12:31:24 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/17 20:49:20 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CommandMap.hpp"
#include "reply.h"
#include "Client.hpp"

#include <cctype>
#include <sstream>

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
static bool __is_nickname_taken(Server const& server, std::string const& nickname);

// valid nickname characters:
// []\`_^{}|a-zZ-Z0-9-
// first character must not be a digit
// length range: 1-9
void cmd_nick(CommandContext& context)
{
	Client& client = context.client;
	Server& server = *client.server;
	std::string const& line = context.line;


	if (line.empty())
		client.reply(ERR_NONICKNAMEGIVEN, ":No nickname given");
	else
	{
		// TODO extract nickname
		if (!__is_nickname_valid(line))
			client.reply(ERR_ERRONEUSNICKNAME, line + " :Erroneous nickname");
		else if (__is_nickname_taken(*client.server, line))
			client.reply(ERR_NICKNAMEINUSE, line + " :Nickname is already in use");
		else
		{
			client.nickname = line;
			std::cout << "Server           |   New nickname: \"" << client.nickname << "\"\n";
			// TODO check if NICK and USER have been sent
			if (!client.isLogged) // && client.nickname && client.info)
			{
				if (server.password == client.password.value)
				{
					std::stringstream ss;

					ss
						<< "Welcome to the jungle "
						<< client.nickname
						<< '!'
						<< client.info.value.username
						<< '@'
						<< "host" // TODO
					;

					client.isLogged = true;
					client.reply(RPL_WELCOME, ss.str());
				}
				else
					client.reply(ERR_PASSWDMISMATCH, ":Password incorrect"); // TODO check if this is the way the protocol is supposed to behave
			}
		}
	}
}

// TODO
static bool __is_nickname_valid(std::string const& nickname)
{
	static std::string const SPECIAL_CHARS("-[]\\`_^{}|");
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
		is_valid |= (std::find(SPECIAL_CHARS.begin(), SPECIAL_CHARS.end(), c) != SPECIAL_CHARS.end());
	}
	return is_valid;
}

// TODO
static bool __is_nickname_taken(Server const& server, std::string const& nickname)
{
	(void)server;
	(void)nickname;
	return false;
}
