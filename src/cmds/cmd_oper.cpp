/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_oper.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 02:38:39 by bbrassar          #+#    #+#             */
/*   Updated: 2022/12/13 20:59:50 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include "command.h"
#include "Reply.hpp"
#include "wildcard.h"

void cmd_oper(CommandContext& ctx)
{
	Client& client = ctx.client;

	if (client.checkState(CLIENT_STATE_OPERATOR)) // client is already operator
		return;

	Server& server = ctx.server;
	Server::OperatorPasswordList::const_iterator it;
	CommandContext::ArgumentList& args = ctx.args;

	if (args.size() < 2)
	{
		client.reply<ERR_NEEDMOREPARAMS>(ctx.name);
		return;
	}

	std::string const& name = args[0];
	std::string const& password = args[1];

	for (it = server.operatorPasswords.begin(); it != server.operatorPasswords.end(); ++it)
	{
		if (name == it->name && wildcardMatch(it->host, client.hostname) && password == it->password)
		{
			client.reply<RPL_YOUREOPER>();
			client.setState(CLIENT_STATE_OPERATOR);
			return;
		}
	}
	client.reply<ERR_PASSWDMISMATCH>();
}
