/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_die.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parallels <parallels@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 02:46:53 by bbrassar          #+#    #+#             */
/*   Updated: 2022/12/14 11:25:18 by parallels        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.h"
#include "command.h"
#include "Client.hpp"

void cmd_die(CommandContext& ctx)
{
	Client& client = ctx.client;

	if (client.checkState(CLIENT_STATE_OPERATOR)) {
		g_Mode = 0;
	}
	else
		client.reply<ERR_NOPRIVILEGES>();
}
