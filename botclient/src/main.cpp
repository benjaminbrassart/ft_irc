/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 07:57:48 by estoffel          #+#    #+#             */
/*   Updated: 2022/12/18 17:32:29 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bot.hpp"
#include "InputContext.hpp"
#include "MessageRegistry.hpp"

#include <algorithm>
#include <deque>
#include <fstream>
#include <iostream>
#include <map>
#include <string>

static void __interpretInput(Bot& bot, std::string const& message, std::deque< std::string >& args);

typedef std::map< std::string, InputHandler > CommandMap;

static CommandMap commandMap;

int	main(int ac, char **av) {

	Bot bot;

	(void)ac;
	(void)av;

	commandMap["ERROR"] = &Bot::onError;
	commandMap["INVITE"] = &Bot::onInvite;
	commandMap["PART"] = &Bot::onPart;
	commandMap["PRIVMSG"] = &Bot::onMessage;

	std::ifstream input;

	input.open("messages.txt");

	if (!input)
	{
		std::cerr << "Unable to open message file\n";
		return 1;
	}

	MessageRegistry mr;

	mr.load(input);

	std::string line;
	std::string::iterator it, fast;
	std::deque< std::string > args;

	// for now read from stdin
	while (std::getline(std::cin, line))
	{
		// skip empty lines
		if (line.empty())
			continue;
		std::cout << line << '\n';
		it = line.begin();
		while (it != line.end())
		{
			// TODO some input may be ':ft_ble :bbrassar!Benjamin@10.0.4.1 INVITE '

			// the first argument will begin with a colon, skip it
			if (it != line.begin() && *it == ':')
			{
				// long argument, directly go to the end
				fast = line.end();
				++it;
			}
			else
			{
				// find next space
				fast = std::find(it, line.end(), ' ');
			}
			args.push_back(std::string(it, fast));
			it = fast;
			// skip space
			if (it != line.end())
				++it;
		}

		// remove server name
		args.pop_front();

		if (!args.empty())
		{
			// get what the server is trying to say
			std::string const message = args.front();

			// remove it from the queue
			args.pop_front();
			__interpretInput(bot, message, args);
		}
	}
}

static void __interpretInput(Bot& bot, std::string const& message, std::deque< std::string >& args)
{
	std::string::const_iterator it = message.begin();
	unsigned int count = 0;

	while (count < 3 && it != message.end() && *it >= '0' && *it <= '9')
	{
		++count;
		++it;
	}

	if (count > 0 && it == message.end())
	{
		// we got a numeric response
	}
	else if (count == 0)
	{
		// we may have a command message
		CommandMap::iterator cmdIt = commandMap.find(message);

		if (cmdIt != commandMap.end())
		{
			InputContext ctx(message, args);

			// found a handler for this command
			if (cmdIt->second != NULL)
				(bot.*cmdIt->second)(ctx);
		}
	}
	// any other input is discarded
}
	Bot	Mee1;

	if (ac != 3) {
		std::cerr << "Wrong number of arguments" << std::endl;
		return 1;
	}
	try
	{
		Mee1.connectClient(av[1], av[2]);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return 1;
	}
	return 0;
}
