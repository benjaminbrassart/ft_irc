/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_motd.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 00:23:13 by bbrassar          #+#    #+#             */
/*   Updated: 2022/12/02 17:38:09 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include "CommandMap.hpp"
#include "config.h"
#include "Reply.hpp"
#include <fstream>

void cmd_motd(CommandContext& context)
{
	Client& client = context.client;
	std::ifstream file;
	std::string line;

	file.open("motd.txt");
	if (file)
	{
		client.reply<RPL_MOTDSTART>(SERVER_NAME);
		while (std::getline(file, line))
			client.reply<RPL_MOTD>(line.substr(0, 80));
		client.reply<RPL_ENDOFMOTD>();
	}
	else
		client.reply<ERR_NOMOTD>();
}
