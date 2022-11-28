/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estoffel <estoffel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 00:55:38 by estoffel          #+#    #+#             */
/*   Updated: 2022/11/28 21:33:09 by estoffel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include "Client.hpp"
#include "Reply.hpp"
#include "Server.hpp"

#include "wildcard.h"
#include "config.h"

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <algorithm>

long	parsing_input(int ac, char *str) {

	if (ac != 3) {
		std::cerr << "Wrong number of arguments -> \"./ircserv <port> <password>\"\n";
		return -1;
	}
	char	*buf;
	long	l = strtol(str, &buf, 10);
	if (l < 0 || l > 65535) {
		std::cerr << "Port number is out of range" << std::endl;
		return -1;
	}
	if (strcmp(buf, "\0")) {
		std::cerr << "Port number is rubbish!" << std::endl;
		return -1;
	}
	return l;
}

//./ircserv <port> <password>
int	main(int ac, char **av) {

	long	port;
	Server	server;

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

	// std::cout << "  IN/OUT  \033[37m|\033[0m     IP ADDR     \033[37m|\033[0m          COMMAND" << '\n';

	Client client = Client(server);
	std::ifstream input;
	std::string line;

	server.name = "ft_ble";
	server.password = "farzar";
	server.motdFileName = "motd.txt";

	server.loadOperatorFile("operators.txt");

	port = parsing_input(ac, av[1]);
	if (port == -1)
		return 1;
	try
	{
		server.__socket(port);
	}
	catch (Server::IoException const& e)
	{
		std::cerr << "I/O error: " << e.what() << std::endl;
	}

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

	input.open("input.txt", std::ifstream::in);
	if (input.fail())
	{
		input.close();
		std::cerr << "Failed to open " << av[1] << '\n';
		return 1;
	}

	while (std::getline(input, line))
		server.processCommand(client, line);

	close(server.getsocketfd());
	// close(server.getclientfd());
	return 0;
}

// static void __testWildcard(std::string const& pattern, std::string const& str)
// {
// 	std::cout
// 		<< "Pattern: '" << pattern << '\'' << '\n'
// 		<< "String:  '" << str << '\'' << '\n'
// 		<< "Matches: " << wildcardMatch(pattern, str) << '\n' << '\n';
// }
