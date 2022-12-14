/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_restart.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parallels <parallels@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 00:00:44 by parallels         #+#    #+#             */
/*   Updated: 2022/12/14 11:25:06 by parallels        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.h"
#include "command.h"
#include "Client.hpp"

void cmd_restart(CommandContext& ctx)
{
	Client& client = ctx.client;

	if (!client.checkState(CLIENT_STATE_OPERATOR))
		client.reply<ERR_NOPRIVILEGES>();
	else {
		g_Mode = 2;
	}
}