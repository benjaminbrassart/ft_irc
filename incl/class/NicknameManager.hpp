/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NicknameManager.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 15:11:05 by bbrassar          #+#    #+#             */
/*   Updated: 2022/12/17 05:18:20 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <map>
#include <set>
#include <string>

class Client;

class NicknameManager
{
public:
	typedef std::map< std::string, Client* > container_type;
	typedef container_type::iterator iterator;

private:
	container_type _nicknames;

public:
	NicknameManager();
	~NicknameManager();

public:
	bool registerNickname(std::string const& nickname, Client* client);
	bool unregisterNickname(std::string const& nickname);
	bool hasNickname(std::string const& nickname);
	iterator getClient(std::string const& nickname);

	void clear();

public:
	iterator begin();
	iterator end();
}; // class NicknameManager
