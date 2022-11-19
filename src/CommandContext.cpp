/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandContext.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 11:47:46 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/19 03:47:54 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CommandMap.hpp"
#include <algorithm>

CommandContext::CommandContext(Client& client, std::string const& prefix, std::string const& line) :
	client(client),
	prefix(prefix),
	line(line)
{
}

CommandContext::~CommandContext()
{}

std::vector< std::string > CommandContext::splitArguments(std::string const& line)
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
		fast = std::find(it, line.end(), ' ');
		args[count++] = std::string(it, fast);
		it = fast;
		if (it != line.end())
			++it;
	}
	return std::vector< std::string >(&args[0], &args[count]);
}
