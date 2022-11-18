/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandMap.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 18:38:48 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/19 00:50:02 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDMAP_HPP
# define COMMANDMAP_HPP

# include "command.h"

# include <map>
# include <string>

class Client;

class CommandMap
{
public:
	typedef void (*Handler)(::CommandContext& context);
	typedef std::pair< Handler, int > HandlerPair;
	typedef std::map< std::string, HandlerPair > MapType;

private:
	MapType _commands;

public:
	CommandMap(void);
	CommandMap(CommandMap const &x);
	CommandMap &operator=(CommandMap const &x);
	~CommandMap();

public:
	void put(std::string const& name, Handler handler, int requiredFlags = 0);
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
