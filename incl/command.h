/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 18:40:51 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/23 02:21:19 by bbrassar         ###   ########.fr       */
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

	static ArgumentList split(std::string const& line, char delim = ' ');
}; // struct CommandContext

typedef void (*CommandHandler)(CommandContext& context);

void cmd_pass(CommandContext& context);
void cmd_user(CommandContext& context);
void cmd_nick(CommandContext& context);
void cmd_quit(CommandContext& context);
void cmd_join(CommandContext& context);
void cmd_mode(CommandContext& context);
void cmd_motd(CommandContext& context);
void cmd_oper(CommandContext& context);

#endif // COMMAND_H
