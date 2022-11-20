/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bbrassar.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 20:42:27 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/19 04:15:51 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include "Reply.hpp"
#include "wildcard.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <algorithm>

// static void __testWildcard(std::string const& pattern, std::string const& str);

int main(int argc, char const* argv[])
{
	// {
	// 	std::cout << "Tests wildcard\n\n";
	// 	std::cout << std::boolalpha;

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

	// 	return 0;
	// }

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

// static void __testWildcard(std::string const& pattern, std::string const& str)
// {
// 	std::cout
// 		<< "Pattern: '" << pattern << '\'' << '\n'
// 		<< "String:  '" << str << '\'' << '\n'
// 		<< "Matches: " << wildcardMatch(pattern, str) << '\n' << '\n';
// }
