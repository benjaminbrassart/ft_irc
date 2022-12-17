/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConnectionManager.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 10:54:39 by bbrassar          #+#    #+#             */
/*   Updated: 2022/12/17 06:59:12 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "class/ConnectionManager.hpp"
#include "class/exception/IOException.hpp"

#include "ft_irc.h"
#include "Client.hpp"
#include "Server.hpp"

#include <cerrno>
#include <cstring>
#include <unistd.h>

ConnectionManager::ConnectionManager() :
	_pollFds(),
	_newConnections()
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
	this->_removedSockets.push_back(sock);
}

void ConnectionManager::wait()
{
	int	poll_res;
	int	errnum;

	poll_res = ::poll(&this->_pollFds[0], this->_pollFds.size(), -1);
	if (poll_res == -1)
	{
		errnum = errno;
		if (errnum != EINTR)
			throw IOException("poll", errnum);
	}
}

void ConnectionManager::handlePoll(Server& server)
{
	iterator it;

	for (it = this->begin(); g_Mode == 1 && it != this->end();)
	{
		if (it->revents & POLLERR)
			this->handlePollErr(server, it);
		else if (it->revents & POLLIN)
			this->handlePollIn(server, it);
		else if (it->revents & POLLOUT)
			this->handlePollOut(server, it);
		else
			++it;
	}

	this->_pollFds.insert(this->_pollFds.end(), this->_newConnections.begin(), this->_newConnections.end());
	this->_newConnections.clear();
	this->__eraseSockets();
}

void ConnectionManager::disconnectClient(Client& client)
{
	client.closeConnection();
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

	::close(it->fd);
	this->removeSocket(it->fd);
	++it;
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
	ClientManager::iterator clientIt = server.clientManager.getClient(it->fd);
	Client::ChannelList::iterator chanIt;

	if (clientIt != server.clientManager.end())
	{
		if (clientIt->second.readFrom())
		{
			chanIt = clientIt->second.channels.begin();
			for (; chanIt != clientIt->second.channels.end(); ++chanIt)
			{
				(*chanIt)->removeClient(clientIt->second);
				if ((*chanIt)->empty())
					server.channelManager.removeChannel((*chanIt)->name);
			}
			clientIt->second.closeConnection();
			server.nickManager.unregisterNickname(clientIt->second.nickname);
			server.clientManager.removeClient(clientIt);
			this->removeSocket(it->fd);
		}
	}
	else
	{
		server.logger.log(ERROR, "Internal error: unable to find connected client");
		this->removeSocket(it->fd);
	}
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
		server.logger.log(DEBUG, "<" + addr + "> New connection");
		this->_newConnections.push_back(pfd);
		server.clientManager.addClient(Client(&server, pfd.fd, addr));
	}
	++it;
}

void ConnectionManager::handlePollOut(Server& server, iterator& it)
{
	ClientManager::iterator clientIt = server.clientManager.getClient(it->fd);

	if (clientIt == server.clientManager.end())
	{
		server.logger.log(ERROR, "Internal error: unable to find connected client");
		this->removeSocket(it->fd);
	}
	else
	{
		clientIt->second.flushWriteBuffer();
		if (clientIt->second.shouldClose)
		{
			clientIt->second.server->nickManager.unregisterNickname(clientIt->second.nickname);
			this->removeSocket(clientIt->first);
			clientIt->second.closeConnection();
		}
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

void ConnectionManager::__eraseSockets()
{
	std::vector< int >::iterator sockIt;
	iterator it;

	for (sockIt = this->_removedSockets.begin(); sockIt != this->_removedSockets.end(); ++sockIt)
	{
		for (it = this->_pollFds.begin(); it != this->_pollFds.end(); ++it)
		{
			if (it->fd == *sockIt)
			{
				this->_pollFds.erase(it);
				break;
			}
		}
	}
	this->_removedSockets.clear();
}

void ConnectionManager::clear()
{
	this->_pollFds.clear();
}
