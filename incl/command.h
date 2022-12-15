/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 18:40:51 by bbrassar          #+#    #+#             */
/*   Updated: 2022/12/15 02:34:09 by bbrassar         ###   ########.fr       */
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

	private:
	static ArgumentList __split(std::string const& line, char separator, bool colon);
}; // struct CommandContext

typedef void (*CommandHandler)(CommandContext& ctx);

void cmd_pass(CommandContext& ctx);
void cmd_user(CommandContext& ctx);
void cmd_nick(CommandContext& ctx);
void cmd_quit(CommandContext& ctx);
void cmd_join(CommandContext& ctx);
void cmd_part(CommandContext& ctx);
void cmd_motd(CommandContext& ctx);
void cmd_oper(CommandContext& ctx);
void cmd_mode(CommandContext& ctx);
void cmd_die(CommandContext& ctx);
void cmd_kill(CommandContext& ctx);
void cmd_ping(CommandContext& ctx);
void cmd_pong(CommandContext& ctx);
void cmd_restart(CommandContext& ctx);
void cmd_privmsg(CommandContext& ctx);
void cmd_notice(CommandContext& ctx);
void cmd_topic(CommandContext& ctx);
void cmd_kick(CommandContext& ctx);
void cmd_list(CommandContext& ctx);
void cmd_names(CommandContext& ctx);

#endif // COMMAND_H
