/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InputContext.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 13:45:29 by bbrassar          #+#    #+#             */
/*   Updated: 2022/12/19 15:57:09 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "InputContext.hpp"
#include <algorithm>

InputContext::InputContext(std::string const& message, Args& args) :
	message(message),
	args(args)
{}

InputContext::~InputContext()
{}

InputContext::Args InputContext::split(std::string const& line)
{
	Args args;
	std::string::const_iterator it = line.begin();
	std::string::const_iterator fast;

	while (it != line.end())
	{
		if (*it == ':')
		{
			fast = line.end();
			++it;
		}
		else
			fast = std::find(it, line.end(), ' ');

		args.push_back(std::string(it, fast));
		it = fast;
		if (it != line.end())
			++it;
	}
	return args;
}
