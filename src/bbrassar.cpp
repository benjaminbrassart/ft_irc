/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bbrassar.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 20:42:27 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/16 18:36:42 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include "reply.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <algorithm>

int main(int argc, char const* argv[])
{
	Server server;
	Client client;
	std::ifstream input;
	std::string line;

	if (argc < 2)
		return 1;

	server.commands.put("CAP", cmd_ignore);
	server.commands.put("PASS", cmd_pass);
	server.commands.put("USER", cmd_user);
	server.commands.put("NICK", cmd_nick);
	server.commands.put("QUIT", cmd_quit);

	input.open("input.txt", std::ifstream::in);
	if (input.fail())
	{
		input.close();
		std::cerr << "Failed to open " << argv[1] << '\n';
		return 1;
	}

	while (std::getline(input, line))
	{
		std::string prefix;
		std::string params;
		std::string::iterator begin;
		std::string::iterator it;

		if (line.empty())
			server.commands.handleUnknownCommand(client, "");
		else
		{
			begin = line.begin();

			// extract prefix if any
			if (*begin == ':')
			{
				it = std::find(begin, line.end(), ' ');
				prefix = std::string(begin, it);
				begin = it;
				if (begin != line.end())
					++begin;
			}

			// extract command name
			it = std::find(begin, line.end(), ' ');

			// extract the rest of the line if any
			if (it != line.end())
				params = std::string(it + 1, line.end());

			server.commands.dispatch(client, prefix, std::string(begin, it), params);
		}
	}
}
