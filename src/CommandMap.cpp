/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandMap.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 18:45:50 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/16 18:45:14 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include "CommandMap.hpp"
#include "reply.h"

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

void CommandMap::put(std::string const& name, CommandMap::Handler handler)
{
	this->_commands[name] = handler;
}

void CommandMap::dispatch(Client& client, std::string const& prefix, std::string const& name, std::string const& line)
{
	CommandMap::MapType::const_iterator it;

	it = this->_commands.find(name);
	if (it == this->_commands.end())
		this->handleUnknownCommand(client, name);
	else
	{
		CommandContext ctx(client, prefix, line);
		it->second(ctx);
	}
}

void CommandMap::handleUnknownCommand(Client& client, std::string const& name)
{
	client.reply(ERR_UNKNOWNCOMMAND, name + " :Unknown command");
}
