/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandMap.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 18:38:48 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/16 18:44:15 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDMAP_HPP
# define COMMANDMAP_HPP

# include <map>
# include <string>

class Client;

struct CommandContext
{
	Client& client;
	std::string const& prefix;
	std::string const& line;

	CommandContext(Client& client, std::string const& prefix, std::string const& line);
	~CommandContext();
}; // struct CommandContext

class CommandMap
{
public:
	typedef void (*Handler)(::CommandContext& context);
	typedef std::map< std::string, Handler > MapType;

private:
	MapType _commands;

public:
	CommandMap(void);
	CommandMap(CommandMap const &x);
	CommandMap &operator=(CommandMap const &x);
	~CommandMap();

public:
	void put(std::string const& name, Handler handler);
	void dispatch(Client& client, std::string const& prefix, std::string const& name, std::string const& line);

public:
	void handleUnknownCommand(Client& client, std::string const& name);
}; // class CommandMap

void cmd_ignore(CommandContext& context);
void cmd_pass(CommandContext& context);
void cmd_user(CommandContext& context);
void cmd_nick(CommandContext& context);
void cmd_quit(CommandContext& context);

#endif // COMMANDMAP_HPP
