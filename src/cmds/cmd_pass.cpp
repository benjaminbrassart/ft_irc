/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pass.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 11:50:58 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/23 02:22:51 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include "CommandMap.hpp"
#include "Reply.hpp"

void cmd_pass(CommandContext& context)
{
	Client& client = context.client;
	CommandContext::ArgumentList& args = context.args;

	if (client.checkState(CLIENT_STATE_PASS))
		client.reply<ERR_ALREADYREGISTRED>();
	else if (args.empty())
		client.reply<ERR_NEEDMOREPARAMS>(context.name);
	else if (args[0] != client.server->password)
		client.reply<ERR_PASSWDMISMATCH>();
	else
		client.setState(CLIENT_STATE_PASS);
}
