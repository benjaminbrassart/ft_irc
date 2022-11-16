/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_user.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 12:01:23 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/16 12:30:55 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

void cmd_user(CommandContext& context)
{
	Client& client = context.client;

	if (client.is_logged || client.info)
		client.reply(ERR_ALREADYREGISTRED, ":Unauthorized command (already registered)");
	else
	{
		// TODO
	}
}
