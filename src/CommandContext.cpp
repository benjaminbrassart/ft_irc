/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandContext.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 11:47:46 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/22 23:31:25 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include "CommandMap.hpp"
#include <algorithm>

CommandContext::CommandContext(Client& client, std::string const& line) :
	client(client),
	server(*client.server),
	args(CommandContext::split(line, ' '))
{
}

CommandContext::~CommandContext()
{}

CommandContext::ArgumentList CommandContext::split(std::string const& line, char delim)
{
	std::string args[15];
	std::string::const_iterator it;
	std::string::const_iterator fast;
	unsigned int count;

	count = 0;
	it = line.begin();
	while (count < (sizeof (args) / sizeof (*args)) && it != line.end())
	{
		if (*it == ':')
		{
			args[count++] = std::string(++it, line.end());
			break;
		}
		fast = std::find(it, line.end(), delim);
		args[count++] = std::string(it, fast);
		it = fast;
		if (it != line.end())
			++it;
	}
	return std::vector< std::string >(&args[0], &args[count]);
}
