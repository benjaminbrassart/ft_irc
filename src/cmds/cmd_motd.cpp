/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_motd.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 00:23:13 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/29 08:09:24 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include "CommandMap.hpp"
#include "Reply.hpp"
#include <fstream>

void cmd_motd(CommandContext& context)
{
	Client& client = context.client;
	Server& server = context.server;
	std::ifstream file;
	std::string line;

	file.open(server.motdFileName.c_str());
	if (file)
	{
		client.reply<RPL_MOTDSTART>(server.name);
		while (std::getline(file, line))
			client.reply<RPL_MOTD>(line.substr(0, 80));
		client.reply<RPL_ENDOFMOTD>();
	}
	else
		client.reply<ERR_NOMOTD>();
}
