/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pong.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 12:39:44 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/29 12:40:48 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include "command.h"

void cmd_pong(CommandContext& ctx)
{
	Client& client = ctx.client;
	Server& server = ctx.server;

	(void)client;
	(void)server;
	// TODO
}
