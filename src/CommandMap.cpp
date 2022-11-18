/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandMap.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 18:45:50 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/18 20:22:08 by bbrassar         ###   ########.fr       */
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

void CommandMap::put(std::string const& command, CommandMap::Handler handler)
{
	this->_commands[command] = handler;
}

void CommandMap::dispatch(Client& client, std::string const& prefix, std::string const& command, std::string const& line)
{
	CommandMap::MapType::const_iterator it;

	it = this->_commands.find(command);
	if (it == this->_commands.end())
		this->handleUnknownCommand(client, command);
	else
	{
		CommandContext ctx(client, prefix, line);
		it->second(ctx);
	}
}

void CommandMap::handleUnknownCommand(Client& client, std::string const& command)
{
	client.reply<ERR_UNKNOWNCOMMAND>(command);
}
