/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bbrassar.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 20:42:27 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/25 10:55:45 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include "Reply.hpp"
#include "wildcard.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <algorithm>

#include "config.h"


int main(int argc, char const* argv[])
{
	std::cout
		<< "Starting ircserv version " << VERSION << '\n'
		<< "Build date: " << STR(BUILD_DATE) << '\n';

	// 	__testWildcard("*", "ABC");
	// 	__testWildcard("*", "");
	// 	__testWildcard("", "A");
	// 	__testWildcard("DDD", "ABC");
	// 	__testWildcard("AB?", "ABC");
	// 	__testWildcard("A?C", "ABC");
	// 	__testWildcard("*@bbrassar.fr", "benjamin@bbrassar.fr");
	// 	__testWildcard("*.fr", "benjamin@bbrassar.fr");
	// 	__testWildcard("*.fr", "benjamin@test.bbrassar.fr");
	// 	__testWildcard("????", "ABC");
	// 	__testWildcard("****", "ABC");
	// 	__testWildcard("*@*.*", "benjamin@localhost");
	// 	__testWildcard("*@*.*", "benjamin@localhost.local");
	// 	__testWildcard("*?", "ABC");
	// 	__testWildcard("?*", "ABC");
	// 	__testWildcard("A?C", "ABC");

	std::cout << "  IN/OUT  \033[37m|\033[0m     IP ADDR     \033[37m|\033[0m          COMMAND" << '\n';

	Server server;
	Client client = Client(server);
	std::ifstream input;
	std::string line;

	client.address.sin_addr.s_addr = inet_addr("127.0.0.1");

	server.name = "ft_ble";
	server.password = "farzar";
	server.motdFileName = "motd.txt";

	server.loadOperatorFile("operators.txt");

	if (argc < 2)
		return 1;

	server.commands.put("CAP", NULL);
	server.commands.put("PASS", cmd_pass);
	server.commands.put("USER", cmd_user, CLIENT_STATE_PASS);
	server.commands.put("NICK", cmd_nick, CLIENT_STATE_PASS);
	server.commands.put("QUIT", cmd_quit, CLIENT_STATE_LOGGED);
	server.commands.put("MOTD", cmd_motd, CLIENT_STATE_LOGGED);
	server.commands.put("OPER", cmd_oper, CLIENT_STATE_LOGGED);
	server.commands.put("JOIN", cmd_join, CLIENT_STATE_LOGGED);
	server.commands.put("PART", cmd_part, CLIENT_STATE_LOGGED);
	server.commands.put("DIE", cmd_die, CLIENT_STATE_LOGGED);
	server.commands.put("KILL", cmd_kill, CLIENT_STATE_LOGGED);
	server.commands.put("NOTICE", cmd_notice, CLIENT_STATE_LOGGED);
	server.commands.put("PRIVMSG", cmd_privmsg, CLIENT_STATE_LOGGED);

	server.clients.push_back(client);

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

// static void __testWildcard(std::string const& pattern, std::string const& str)
// {
// 	std::cout
// 		<< "Pattern: '" << pattern << '\'' << '\n'
// 		<< "String:  '" << str << '\'' << '\n'
// 		<< "Matches: " << wildcardMatch(pattern, str) << '\n' << '\n';
// }
