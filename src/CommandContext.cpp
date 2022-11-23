/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandContext.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 11:47:46 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/23 02:21:31 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include "CommandMap.hpp"
#include <algorithm>

#define SIZEOF_ARRAY(Array) (sizeof (Array) / sizeof (*Array))

CommandContext::CommandContext(Client& client, std::string const& name, std::string const& line) :
	client(client),
	server(*client.server),
	name(name),
	args(CommandContext::split(line, ' '))
{
}

CommandContext::~CommandContext()
{}

CommandContext::ArgumentList CommandContext::split(std::string const& line, char delim)
{
	std::string args[15];
	std::string first;
	std::string::const_iterator it;
	std::string::const_iterator first_it;
	std::string::const_iterator fast;
	unsigned int count;

	count = 0;
	it = std::find(line.begin(), line.end(), ':');

	if (it != line.begin())
	{
		if (it != line.end())
			--it;
		first_it = line.begin();
		while (count < SIZEOF_ARRAY(args) && first_it != it)
		{
			fast = std::find(first_it, it, delim);
			args[count++] = std::string(first_it, fast);
			first_it = fast;
			if (first_it != it)
				++first_it;
		}
		if (it != line.end())
			++it;
	}

	while (count < SIZEOF_ARRAY(args) && it != line.end())
	{
		if (it != line.end() && *it == ':')
			++it;
		fast = std::find(it, line.end(), ':');
		args[count++] = std::string(it, fast);
		it = fast;
		if (it != line.end())
			++it;
	}
	return std::vector< std::string >(&args[0], &args[count]);
}
