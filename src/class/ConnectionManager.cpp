/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConnectionManager.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 10:54:39 by bbrassar          #+#    #+#             */
/*   Updated: 2022/12/03 12:28:20 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "class/ConnectionManager.hpp"
#include "class/exception/IOException.hpp"
#include "Server.hpp"
#include <cerrno>
#include <cstring>

ConnectionManager::ConnectionManager() :
	_pollFds()
{
}

ConnectionManager::~ConnectionManager()
{}

void ConnectionManager::setServer(Server& server)
{
	::pollfd pfd = {
		.fd = server.sockFd,
		.events = POLLIN,
		.revents = 0,
	};

	this->_pollFds.push_back(pfd);
}

void ConnectionManager::removeSocket(int sock)
{
	for (iterator it = this->_pollFds.begin(); it != this->_pollFds.end(); ++it)
	{
		if (it->fd == sock)
		{
			this->_pollFds.erase(it);
			return;
		}
	}
}

void ConnectionManager::wait()
{
	int	poll_res;

	poll_res = ::poll(&this->_pollFds[0], this->_pollFds.size(), -1);
	if (poll_res == -1)
		throw IOException("poll", errno);
}

void ConnectionManager::handlePoll(Server& server)
{
	for (iterator it = this->begin(); it != this->end();)
	{
		if (it->events & POLLERR)
			this->handlePollErr(server, it);
		else if (it->events & POLLIN)
			this->handlePollIn(server, it);
		else if (it->events & POLLOUT)
			this->handlePollOut(server, it);
		else
			++it;
	}
}

void ConnectionManager::handlePollErr(Server& server, iterator& it)
{
	int errnum;
	::socklen_t errnum_len;
	std::string error;

	errnum_len = sizeof (errnum);
	error = std::string("Error on socket ") + it->fd + ": ";
	if (getsockopt(it->fd, SOL_SOCKET, SO_ERROR, &errnum, &errnum_len) == -1)
		error += "Unknown error";
	else
		error += std::strerror(errnum);
	server.logger.log(ERROR, error);

	ClientManager::iterator clientIt = server.clientManager.getClient(it->fd);

	if (clientIt != server.clientManager.end())
	{
		server.nickManager.unregisterNickname(clientIt->second.nickname);
		server.clientManager.removeClient(clientIt);
	}

	this->_pollFds.erase(it);
}

void ConnectionManager::handlePollIn(Server& server, iterator& it)
{
	if (it->fd == server.sockFd)
		this->handlePollInServer(server, it);
	else
		this->handlePollInClient(server, it);
}

void ConnectionManager::handlePollInClient(Server& server, iterator& it)
{
	(void)server;
	++it;
}

void ConnectionManager::handlePollInServer(Server& server, iterator& it)
{
	int errnum;
	::sockaddr_in addr;
	::socklen_t addr_len = sizeof (addr);
	::pollfd pfd = {
		.fd = ::accept(it->fd, reinterpret_cast< ::sockaddr* >(&addr), &addr_len),
		.events = POLLIN | POLLOUT,
		.revents = 0,
	};

	if (pfd.fd == -1)
	{
		errnum = errno;
		server.logger.log(INFO, std::string("Unable to accept connection: ") + std::strerror(errnum));
	}
	else
	{
		this->_pollFds.push_back(pfd);
		server.clientManager.addClient(Client(&server, pfd.fd, addr));
	}
	++it;
}

void ConnectionManager::handlePollOut(Server& server, iterator& it)
{
	ClientManager::iterator clientIt = server.clientManager.getClient(it->fd);

	if (clientIt == server.clientManager.end())
	{
		server.logger.log(ERROR, "Internal error: unable to connected client");
		this->_pollFds.erase(it);
	}
	else
	{
		clientIt->second.flushWriteBuffer();
		++it;
	}
}

ConnectionManager::iterator ConnectionManager::begin()
{
	return this->_pollFds.begin();
}

ConnectionManager::iterator ConnectionManager::end()
{
	return this->_pollFds.end();
}
