/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_nick.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 12:31:24 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/16 18:45:16 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CommandMap.hpp"
#include "reply.h"
#include "Client.hpp"

// valid nickname characters:
// []\`_^{}|a-zZ-Z0-9-
// first character must not be a digit
// length range: 1-9
void cmd_nick(CommandContext& context)
{
	Client& client = context.client;
	std::string const& line = context.line;
	std::string nick;

	if (line.empty())
		client.reply(ERR_NONICKNAMEGIVEN, ":No nickname given");
	else
	{
		// TODO extract nickname
		if (false) // TODO check nickname validity
			client.reply(ERR_ERRONEUSNICKNAME, nick + " :Erroneous nickname");
		else if (false) // TODO check if a user with that nickname is already logged
			client.reply(ERR_NICKNAMEINUSE, nick + " :Nickname is already in use");
		else
			client.nickname = nick;
	}
}
