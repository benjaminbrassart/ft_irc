/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_kill.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 03:00:42 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/23 04:52:46 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "Client.hpp"

void cmd_kill(CommandContext& context)
{
	Client& client = context.client;
	CommandContext::ArgumentList& args = context.args;

	if (args.size() < 2)
		client.reply<ERR_NEEDMOREPARAMS>(context.name);
	else if (!client.checkState(CLIENT_STATE_OPERATOR))
		client.reply<ERR_NOPRIVILEGES>();
	else
	{

	}
}
