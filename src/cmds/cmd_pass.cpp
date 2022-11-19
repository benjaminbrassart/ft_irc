/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pass.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 11:50:58 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/19 04:14:51 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include "CommandMap.hpp"
#include "optional.hpp"
#include "Reply.hpp"

void cmd_pass(CommandContext& context)
{
	Client& client = context.client;
	std::string const& line = context.line;

	if (client.checkState(CLIENT_STATE_PASS))
		client.reply<ERR_ALREADYREGISTRED>();
	else if (line.empty())
		client.reply<ERR_NEEDMOREPARAMS>("PASS");
	else if (line != client.server->password)
		client.reply<ERR_PASSWDMISMATCH>();
	else
		client.setState(CLIENT_STATE_PASS);
}
