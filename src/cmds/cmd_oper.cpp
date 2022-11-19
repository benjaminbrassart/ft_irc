/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_oper.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 02:38:39 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/19 02:49:46 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include "CommandMap.hpp"
#include "Reply.hpp"

void cmd_oper(CommandContext& context)
{
	Client& client = context.client;
	Server& server = *client.server;
	std::string name; // TODO
	std::string password; // TODO
	Server::OperatorPasswordMap::const_iterator it;

	// TODO check client host => ERR_NOOPERHOST
	it = server.operatorPasswords.find(name);
	if (it != server.operatorPasswords.end() && it->second == password)
		client.reply<RPL_YOUREOPER>();
	else
		client.reply<ERR_PASSWDMISMATCH>();
}
