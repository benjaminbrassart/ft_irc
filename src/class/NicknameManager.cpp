/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NicknameManager.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 15:13:33 by bbrassar          #+#    #+#             */
/*   Updated: 2022/12/02 15:14:37 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "class/NicknameManager.hpp"

NicknameManager::NicknameManager() :
	_nicknames()
{
}

NicknameManager::~NicknameManager()
{
}

bool NicknameManager::registerNickname(std::string const& nickname)
{
	return this->_nicknames.insert(nickname).second;
}

bool NicknameManager::unregisterNickname(std::string const& nickname)
{
	return this->_nicknames.erase(nickname) > 0;
}

bool NicknameManager::hasNickname(std::string const& nickname)
{
	return this->_nicknames.find(nickname) != this->_nicknames.end();
}
