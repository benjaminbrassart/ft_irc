/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NicknameManager.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 15:11:05 by bbrassar          #+#    #+#             */
/*   Updated: 2022/12/02 15:13:09 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <set>
#include <string>

class NicknameManager
{
public:
	typedef std::set< std::string > container_type;

private:
	container_type _nicknames;

public:
	NicknameManager();
	~NicknameManager();

public:
	bool registerNickname(std::string const& nickname);
	bool unregisterNickname(std::string const& nickname);
	bool hasNickname(std::string const& nickname);
}; // class NicknameManager
