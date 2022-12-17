/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConnectionManager.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 10:54:57 by bbrassar          #+#    #+#             */
/*   Updated: 2022/12/17 05:18:17 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <poll.h>
#include <vector>

class Client;
class Server;

class ConnectionManager
{
public:
	typedef std::vector< ::pollfd > container_type;
	typedef container_type::iterator iterator;

private:
	container_type _pollFds;
	container_type _newConnections;
	std::vector< int > _removedSockets;

public:
	ConnectionManager();
	~ConnectionManager();

public:
	void setServer(Server& server);
	void removeSocket(int sock);
	void wait();
	void handlePoll(Server& server);
	void disconnectClient(Client& client);

	void clear();

public:
	iterator begin();
	iterator end();

private:
	void handlePollErr(Server& server, iterator& it);
	void handlePollIn(Server& server, iterator& it);
	void handlePollOut(Server& server, iterator& it);

	void handlePollInServer(Server& server, iterator& it);
	void handlePollInClient(Server& server, iterator& it);

	void __eraseSockets();
}; // class ConnectionManager
