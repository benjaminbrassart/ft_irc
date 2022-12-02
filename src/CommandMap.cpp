/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandMap.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 18:45:50 by bbrassar          #+#    #+#             */
/*   Updated: 2022/12/02 10:12:13 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include "CommandMap.hpp"
#include "Reply.hpp"

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
