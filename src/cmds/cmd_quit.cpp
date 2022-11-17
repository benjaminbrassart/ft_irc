/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_quit.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 13:50:33 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/16 18:44:44 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include "CommandMap.hpp"

void cmd_quit(CommandContext& context)
{
	Client& client = context.client;
	Client::ChannelList::iterator it;

	for (it = client.channels.begin(); it != client.channels.end(); ++it)
		(*it)->removeClient(client);
	client.send("ERROR :buh-bye"); // TODO define message
	client.closeConnection();
}
