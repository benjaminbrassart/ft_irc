/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 18:40:51 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/29 12:45:17 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# include <string>
# include <vector>

class Client;
class Server;

struct CommandContext
{
	typedef std::vector< std::string > ArgumentList;

	Client& client;
	Server& server;
	std::string name;
	ArgumentList args;

	CommandContext(Client& client, std::string const& name, std::string const& line);
	~CommandContext();

	// split arguments on spaces, with long strings
	static ArgumentList split(std::string const& line);

	// split arguments on comma, without long arguments
	static ArgumentList splitList(std::string const& line);
}; // struct CommandContext

typedef void (*CommandHandler)(CommandContext& context);

void cmd_pass(CommandContext& context);
void cmd_user(CommandContext& context);
void cmd_nick(CommandContext& context);
void cmd_quit(CommandContext& context);
void cmd_join(CommandContext& context);
void cmd_part(CommandContext& context);
void cmd_motd(CommandContext& context);
void cmd_oper(CommandContext& context);
void cmd_die(CommandContext& context);
void cmd_kill(CommandContext& context);
void cmd_ping(CommandContext& context);
void cmd_pong(CommandContext& context);
void cmd_msg_common(CommandContext& ctx); // for both PRIVMSG and NOTICE

#endif // COMMAND_H
