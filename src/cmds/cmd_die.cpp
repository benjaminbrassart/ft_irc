/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_die.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 02:46:53 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/23 02:49:04 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "Client.hpp"

void cmd_die(CommandContext& context)
{
	Client& client = context.client;
	Server& server = context.server;

	if (client.checkState(CLIENT_STATE_OPERATOR))
		server.shutdown();
	else
		client.reply<ERR_NOPRIVILEGES>();
}
