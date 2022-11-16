/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 18:40:51 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/16 21:24:54 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# include <string>
# include <vector>

class Client;

struct CommandContext
{
	Client& client;
	std::string const& prefix;
	std::string const& line;

	CommandContext(Client& client, std::string const& prefix, std::string const& line);
	~CommandContext();
}; // struct CommandContext

typedef void (*CommandHandler)(CommandContext& context);

void cmd_ignore(CommandContext& context);
void cmd_pass(CommandContext& context);
void cmd_user(CommandContext& context);
void cmd_nick(CommandContext& context);
void cmd_quit(CommandContext& context);
void cmd_join(CommandContext& context);

#endif // COMMAND_H
