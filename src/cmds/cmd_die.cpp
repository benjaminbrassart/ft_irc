/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_die.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 02:46:53 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/29 14:51:20 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.h"
#include "command.h"
#include "Client.hpp"

void cmd_die(CommandContext& context)
{
	Client& client = context.client;

	if (client.checkState(CLIENT_STATE_OPERATOR))
		KEEP_RUNNING = false;
	else
		client.reply<ERR_NOPRIVILEGES>();
}
