/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandMap.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 18:38:48 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/19 04:14:18 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDMAP_HPP
# define COMMANDMAP_HPP

# include "command.h"
# include "ClientState.hpp"

# include <map>
# include <string>

class Client;

class CommandMap
{
public:
	typedef void (*Handler)(::CommandContext& context);
	typedef std::pair< Handler, ClientState > HandlerPair;
	typedef std::map< std::string, HandlerPair > MapType;

private:
	MapType _commands;

public:
	CommandMap(void);
	CommandMap(CommandMap const &x);
	CommandMap &operator=(CommandMap const &x);
	~CommandMap();

public:
	void put(std::string const& name, Handler handler, ClientState requiredFlags = CLIENT_STATE_INIT);
	void dispatch(Client& client, std::string const& prefix, std::string const& name, std::string const& line);

public:
	void handleUnknownCommand(Client& client, std::string const& name);
}; // class CommandMap

void cmd_ignore(CommandContext& context);
void cmd_pass(CommandContext& context);
void cmd_user(CommandContext& context);
void cmd_nick(CommandContext& context);
void cmd_quit(CommandContext& context);
void cmd_motd(CommandContext& context);

#endif // COMMANDMAP_HPP
