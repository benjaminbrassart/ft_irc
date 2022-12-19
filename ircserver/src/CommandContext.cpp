/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandContext.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 11:47:46 by bbrassar          #+#    #+#             */
/*   Updated: 2022/12/19 13:09:47 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include "CommandMap.hpp"
#include "command.h"
#include <algorithm>

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
		// if the first character is a colon
		if (colon && *it == ':')
		{
			// skip the colon
			++it;

			// go to the end
			fast = line.end();
		}
		else
		{
			// go to next space
			fast = std::find(it, line.end(), separator);
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
