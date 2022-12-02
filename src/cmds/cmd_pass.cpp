/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pass.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 11:50:58 by bbrassar          #+#    #+#             */
/*   Updated: 2022/12/02 11:12:55 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include "CommandMap.hpp"
#include "Reply.hpp"

void cmd_pass(CommandContext& context)
{
	Client& client = context.client;
	Server& server = context.server;
	CommandContext::ArgumentList& args = context.args;
	std::string const& password = args[0];

	if (client.checkState(CLIENT_STATE_NICK) || client.checkState(CLIENT_STATE_USER))
		client.reply<ERR_ALREADYREGISTRED>();
	else if (args.empty())
		client.reply<ERR_NEEDMOREPARAMS>(context.name);
	else
	{
		client.password = password;
		server.logger.log(DEBUG, "<" + client.address + "> Password set");
	}
}
