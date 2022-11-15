/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandMap.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 18:45:50 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/15 20:59:41 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CommandMap.hpp"

CommandMap::CommandMap() :
	_commands()
{}

CommandMap::CommandMap(CommandMap const& x) :
	_commands(x._commands)
{}

CommandMap& CommandMap::operator=(CommandMap const& x)
{
	this->_commands = x._commands;
	return *this;
}

CommandMap::~CommandMap()
{}

void CommandMap::put(std::string const& name, CommandHandler handler)
{
	this->_commands[name] = handler;
}

void CommandMap::dispatch(Client& client, std::string const& name)
{
	CommandMap::map_type::const_iterator it;

	it = this->_commands.find(name);
	if (it == this->_commands.end())
		this->handleUnknownCommand(client);
	else
		it->second(client);
}

void CommandMap::handleUnknownCommand(Client& client)
{
	(void)client;
}
