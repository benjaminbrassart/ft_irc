/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pass.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 11:50:58 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/18 18:21:59 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include "CommandMap.hpp"
#include "optional.hpp"
#include "reply.h"

void cmd_pass(CommandContext& context)
{
	Client& client = context.client;
	std::string const& line = context.line;

	if (client.isLogged || client.password)
		client.reply<ERR_ALREADYREGISTRED>();
	else if (line.empty())
		client.reply<ERR_NEEDMOREPARAMS>("PASS");
	else
		client.password = make_optional(line);
}
