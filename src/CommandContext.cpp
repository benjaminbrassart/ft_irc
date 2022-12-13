/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandContext.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 11:47:46 by bbrassar          #+#    #+#             */
/*   Updated: 2022/12/13 21:24:13 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include "CommandMap.hpp"
#include "command.h"
#include <algorithm>

#define SIZEOF_ARRAY(Array) (sizeof (Array) / sizeof (*Array))

CommandContext::CommandContext(Client& client, std::string const& name, std::string const& line) :
	client(client),
	server(*client.server),
	name(name),
	args(CommandContext::split(line))
{}

CommandContext::~CommandContext()
{}

CommandContext::ArgumentList CommandContext::split(std::string const& line)
{
	return CommandContext::__split(line, ' ', true);
}

// TODO refactor common code between split and splitList
CommandContext::ArgumentList CommandContext::splitList(std::string const& line)
{
	return CommandContext::__split(line, ',', false);
}

CommandContext::ArgumentList CommandContext::__split(std::string const& line, char separator, bool colon)
{
	ArgumentList args;
	std::string::const_iterator it = line.begin();
	std::string::const_iterator fast;

	while (it != line.end())
	{
		// go to next space
		fast = std::find(it, line.end(), separator);

		// if the first character is a colon...
		if (colon && fast != line.end() && (fast + 1) != line.end() && *it == ':')
		{
			// skip the colon
			++it;

			// go to the end
			fast = line.end();
		}

		// add a new argument
		args.push_back(std::string(it, fast));

		// move the iterator
		it = fast;

		// if not at the end, skip the current space
		if (it != line.end())
			++it;
	}
	return args;
}
