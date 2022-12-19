/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MessageRegistry.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 10:50:27 by bbrassar          #+#    #+#             */
/*   Updated: 2022/12/17 10:53:27 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <istream>
#include <string>
#include <vector>

class MessageRegistry
{
public:
	typedef std::vector< std::string > container_type;

private:
	container_type _messages;

public:
	MessageRegistry();
	~MessageRegistry();

public:
	std::string const& getRandomMessage() const;
	void load(std::istream& input);
	void clear();
}; // class MessageRegistry
