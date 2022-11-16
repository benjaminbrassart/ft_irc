/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 18:40:51 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/16 12:06:02 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# include "Client.hpp"
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

	void reply(int code, std::string const& message);
}; // struct CommandContext

typedef void (*CommandHandler)(CommandContext& context);

void cmd_ignore(CommandContext& context);
void cmd_pass(CommandContext& context);
void cmd_user(CommandContext& context);

#endif // COMMAND_H
