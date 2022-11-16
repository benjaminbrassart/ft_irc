/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bbrassar.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 20:42:27 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/16 13:43:03 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CommandMap.hpp"
#include "command.h"
#include "reply.h"
#include <iostream>
#include <fstream>
#include <stdexcept>

int main(int argc, char const* argv[])
{
	Client client;
	CommandMap commands;
	std::ifstream input;
	std::string line;

	if (argc < 2)
		return 1;

	commands.put("CAP", cmd_ignore);
	commands.put("PASS", cmd_pass);
	commands.put("USER", cmd_user);
	commands.put("NICK", cmd_nick);

	input.open("input.txt", std::ifstream::in);
	if (input.fail())
	{
		input.close();
		std::cerr << "Failed to open " << argv[1] << '\n';
		return 1;
	}

	// TODO limit to 15 command parameters (see rfc2812: 2.3 Messages)
	while (std::getline(input, line))
	{
		std::string prefix;
		std::string params;
		std::string::iterator begin;
		std::string::iterator it;

		if (line.empty())
			commands.handleUnknownCommand(client, "");
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

			commands.dispatch(client, prefix, std::string(begin, it), params);
		}
	}
}
