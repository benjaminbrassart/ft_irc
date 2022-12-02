/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandMap.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 18:45:50 by bbrassar          #+#    #+#             */
/*   Updated: 2022/12/02 16:46:16 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include "CommandMap.hpp"
#include "Reply.hpp"
#include <algorithm>

CommandMap::CommandMap(Server& server) :
	_commands(),
	server(server)
{}

CommandMap::CommandMap(CommandMap const& x) :
	_commands(x._commands),
	server(x.server)
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
	this->server.logger.log(DEBUG, "+ " + command);
}

void CommandMap::process(Client& client, std::string const& line)
{
	std::string prefix;
	std::string params;
	std::string::const_iterator begin;
	std::string::const_iterator it;

	if (line.empty())
		return;
	begin = line.begin();

	// extract prefix if any
	if (*begin == ':')
	{
		it = std::find(begin, line.end(), ' ');
		prefix = std::string(begin, it);
		begin = it;
		if (begin != line.end())
			++begin;
	}

	// extract command name
	it = std::find(begin, line.end(), ' ');

	// extract the rest of the line if any
	if (it != line.end())
		params = std::string(it + 1, line.end());

	// execute the command with the given arguments
	this->dispatch(client, prefix, std::string(begin, it), params);
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
		CommandContext ctx(client, command, line);
		this->server.logger.log(DEBUG, "<" + client.address + "> '" + command + " " + line + "'");
		it->second.first(ctx);
	}
}

void CommandMap::handleUnknownCommand(Client& client, std::string const& command)
{
	this->server.logger.log(DEBUG, "<" + client.address + "> Unknown command '" + command + "'");
	client.reply<ERR_UNKNOWNCOMMAND>(command);
}
