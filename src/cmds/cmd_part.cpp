/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_part.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 14:11:06 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/21 05:00:31 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include "CommandMap.hpp"
#include "Reply.hpp"

void cmd_part(CommandContext& context)
{
	Client& client = context.client;
	std::vector< std::string > const args = CommandContext::splitArguments(context.line, ',');
	std::string::const_iterator chan_it;
	std::string const* message_ptr;

	if (args.empty())
	{
		client.reply<ERR_NEEDMOREPARAMS>("PART");
		return;
	}

	if (args.size() < 2)
		message_ptr = &client.nickname;
	else
		message_ptr = &args[1];

	for (chan_it = args[0].begin(); chan_it != args[0].end(); ++chan_it)
	{
		(void)message_ptr;
	}
}
