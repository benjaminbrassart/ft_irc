/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandMap.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 18:45:50 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/23 01:27:50 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include "CommandMap.hpp"
#include "Reply.hpp"

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

void CommandMap::put(std::string const& command, CommandMap::Handler handler, ClientState requiredFlags)
{
	this->_commands[command] = std::make_pair(handler, requiredFlags);
}

void CommandMap::dispatch(Client& client, std::string const& prefix, std::string const& command, std::string const& line)
{
	CommandMap::MapType::const_iterator it;

	(void)prefix;
	it = this->_commands.find(command);
	if (it == this->_commands.end())
		this->handleUnknownCommand(client, command);
	else if (!(it->second.first == NULL || !client.checkState(it->second.second)))
	{
		CommandContext ctx(client, line);
		it->second.first(ctx);
	}
}

void CommandMap::handleUnknownCommand(Client& client, std::string const& command)
{
	client.reply<ERR_UNKNOWNCOMMAND>(command);
}
