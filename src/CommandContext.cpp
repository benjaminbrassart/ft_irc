/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandContext.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 11:47:46 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/16 12:07:23 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

CommandContext::CommandContext(Client& client, std::string const& prefix, std::string const& line) :
	client(client),
	prefix(prefix),
	line(line)
{
}

CommandContext::~CommandContext()
{}

void CommandContext::reply(Reply code, std::string const& message)
{
	this->client.reply(code, message);
}
