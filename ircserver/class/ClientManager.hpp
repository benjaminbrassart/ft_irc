/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientManager.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 14:55:18 by bbrassar          #+#    #+#             */
/*   Updated: 2022/12/17 05:17:27 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

// #include "Client.hpp"
#include <map>
#include <string>

class Client;

class ClientManager
{
public:
	typedef std::map< int, Client > container_type;
	typedef container_type::iterator iterator;

private:
	container_type _clients;

public:
	ClientManager();
	~ClientManager();

public:
	iterator getClient(int sockFd);
	iterator getClient(std::string const& nickname);

	void addClient(Client const& client);
	void removeClient(iterator it);

	void clear();

	iterator begin();
	iterator end();
}; // class ClientManager
