/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bbrassar.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 20:42:27 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/15 22:18:45 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CommandMap.hpp"
#include <iostream>
#include <fstream>
#include <stdexcept>

void cmd_pass(Client& client, std::vector< std::string > const& args)
{
	static std::string const PASSWORD = "mdp123";
	(void)client;

	if (args.size() != 1)
		return;
	if (PASSWORD == args[0])
		std::cout << "password ok\n";
	else
		std::cout << "password ko :(\n";
}

void cmd_ignore(Client& client, std::vector< std::string > const& args)
{
	(void)client;
	(void)args;
}

int main(int argc, char const* argv[])
{
	Client client;
	CommandMap commands;
	std::ifstream input;
	std::string line;

	if (argc < 2)
		return 1;

	commands.put("PASS", cmd_pass);
	commands.put("CAP", cmd_ignore);
	commands.put("LS", cmd_ignore);

	input.open("input.txt", std::ifstream::in);
	if (input.fail())
	{
		input.close();
		std::cerr << "Failed to open " << argv[1] << '\n';
		return 1;
	}

	while (std::getline(input, line))
	{
		std::vector< std::string > args;
		std::string::const_iterator it;
		std::string::const_iterator fast;

		it = line.begin();
		while (it != line.end())
		{
			while (it != line.end() && (*it == ' ' || *it == '\t'))
				++it;
			fast = it;
			while (fast != line.end() && *fast != ' ' && *fast != '\t')
				++fast;
			if (fast == it)
				break;
			args.push_back(std::string(it, fast));
			it = fast;
		}

		if (args.empty())
			commands.handleUnknownCommand(client);
		else
			commands.dispatch(client, args.front(), std::vector< std::string >(args.begin() + 1, args.end())); // TODO may be kinda slow
	}
}
