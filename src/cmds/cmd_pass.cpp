/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pass.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 11:50:58 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/16 11:55:17 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "reply.h"

void cmd_pass(CommandContext& context)
{
	Client& client = context.client;
	std::string const& line = context.line;

	if (client.is_logged || client.password)
		client.reply(ERR_ALREADYREGISTRED, ":Unauthorized command (already registered)");
	else if (line.empty())
		client.reply(ERR_NEEDMOREPARAMS, "PASS :Not enough parameters");
	else
		client.password = make_optional(line);
}
