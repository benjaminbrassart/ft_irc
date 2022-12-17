/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientManager.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 16:07:30 by bbrassar          #+#    #+#             */
/*   Updated: 2022/12/17 05:18:52 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "class/ClientManager.hpp"
#include "Client.hpp"

ClientManager::ClientManager()
{}

ClientManager::~ClientManager()
{}

ClientManager::iterator ClientManager::getClient(int sockFd)
{
	return this->_clients.find(sockFd);
}

void ClientManager::addClient(Client const& client)
{
	this->_clients[client.sock_fd] = client;
}

void ClientManager::removeClient(iterator it)
{
	this->_clients.erase(it);
}

ClientManager::iterator ClientManager::begin()
{
	return this->_clients.begin();
}

ClientManager::iterator ClientManager::end()
{
	return this->_clients.end();
}

void ClientManager::clear()
{
	this->_clients.clear();
}
