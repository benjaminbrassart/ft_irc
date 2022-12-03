/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConnectionManager.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 10:54:57 by bbrassar          #+#    #+#             */
/*   Updated: 2022/12/03 12:27:09 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <poll.h>
#include <vector>

class Server;

class ConnectionManager
{
public:
	typedef std::vector< ::pollfd > container_type;
	typedef container_type::iterator iterator;

private:
	container_type _pollFds;

public:
	ConnectionManager();
	~ConnectionManager();

public:
	void setServer(Server& server);
	void removeSocket(int sock);
	void wait();
	void handlePoll(Server& server);

public:
	iterator begin();
	iterator end();

private:
	void handlePollErr(Server& server, iterator& it);
	void handlePollIn(Server& server, iterator& it);
	void handlePollOut(Server& server, iterator& it);

	void handlePollInServer(Server& server, iterator& it);
	void handlePollInClient(Server& server, iterator& it);
}; // class ConnectionManager
