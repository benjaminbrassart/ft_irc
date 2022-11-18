/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bbrassar.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 20:42:27 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/19 00:50:59 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include "Reply.hpp"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <algorithm>

int main(int argc, char const* argv[])
{
	Server server;
	Client client = Client(server);
	std::ifstream input;
	std::string line;

	server.name = "ft_ble";
	server.password = "farzar";
	server.motdFileName = "motd.txt";

	if (argc < 2)
		return 1;

	server.commands.put("CAP", cmd_ignore);
	server.commands.put("PASS", cmd_pass);
	server.commands.put("USER", cmd_user, CLIENT_STATE_PASS);
	server.commands.put("NICK", cmd_nick, CLIENT_STATE_PASS);
	server.commands.put("QUIT", cmd_quit, CLIENT_STATE_LOGGED);
	server.commands.put("MOTD", cmd_motd, CLIENT_STATE_LOGGED);

	input.open("input.txt", std::ifstream::in);
	if (input.fail())
	{
		input.close();
		std::cerr << "Failed to open " << argv[1] << '\n';
		return 1;
	}

	while (std::getline(input, line))
		server.processCommand(client, line);
}
