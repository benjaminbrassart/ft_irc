/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandMap.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 18:45:50 by bbrassar          #+#    #+#             */
/*   Updated: 2022/12/02 17:26:29 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include "CommandMap.hpp"
#include "Reply.hpp"
#include <algorithm>

CommandMap::CommandMap(Server& server) :
	_commands(),
	server(server)
{
	this->server.logger.log(DEBUG, "Registering commands");
	this->put("CAP", NULL);
	this->put("PASS", cmd_pass);
	this->put("USER", cmd_user);
	this->put("NICK", cmd_nick);
	this->put("QUIT", cmd_quit, CLIENT_STATE_LOGGED);
	this->put("MOTD", cmd_motd, CLIENT_STATE_LOGGED);
	this->put("OPER", cmd_oper, CLIENT_STATE_LOGGED);
	this->put("JOIN", cmd_join, CLIENT_STATE_LOGGED);
	this->put("PART", cmd_part, CLIENT_STATE_LOGGED);
	this->put("DIE", cmd_die, CLIENT_STATE_LOGGED);
	this->put("KILL", cmd_kill, CLIENT_STATE_LOGGED);
	this->put("NOTICE", cmd_msg_common, CLIENT_STATE_LOGGED);
	this->put("PRIVMSG", cmd_msg_common, CLIENT_STATE_LOGGED);
	this->put("PING", cmd_ping);
	this->put("PONG", cmd_pong);
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
