/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_ping.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 12:39:48 by bbrassar          #+#    #+#             */
/*   Updated: 2022/12/02 11:16:17 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include "command.h"

void cmd_ping(CommandContext& ctx)
{
	Client& client = ctx.client;
	CommandContext::ArgumentList& args = ctx.args;

	if (args.empty())
	{
		client.reply<ERR_NOORIGIN>();
		return;
	}

	client.send("PONG :" + args[0]);
}
