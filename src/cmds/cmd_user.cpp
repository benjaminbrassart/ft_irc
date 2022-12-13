/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_user.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 12:01:23 by bbrassar          #+#    #+#             */
/*   Updated: 2022/12/13 20:59:50 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include "CommandMap.hpp"

void cmd_user(CommandContext& ctx)
{
	Client& client = ctx.client;
	std::vector< std::string >& args = ctx.args;
	std::string mode;

	if (client.checkState(CLIENT_STATE_USER))
		client.reply<ERR_ALREADYREGISTRED>();
	else if (args.size() < 4)
		client.reply<ERR_NEEDMOREPARAMS>(ctx.name);
	else
	{
		client.username = args[0];
		mode = args[1];
		client.hostname = args[2];
		client.realname = args[3];
		client.setState(CLIENT_STATE_USER);
		client.tryLogin();
		// TODO do something with `mode`
	}
}
