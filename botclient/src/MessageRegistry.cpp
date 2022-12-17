/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MessageRegistry.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 10:50:20 by bbrassar          #+#    #+#             */
/*   Updated: 2022/12/17 11:30:52 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MessageRegistry.hpp"
#include <cstdlib>
#include <ctime>

MessageRegistry::MessageRegistry() :
	_messages()
{
	std::srand(std::time(NULL));
}

MessageRegistry::~MessageRegistry()
{}

std::string const& MessageRegistry::getRandomMessage() const
{
	return this->_messages[std::rand() % this->_messages.size()];
}

void MessageRegistry::load(std::istream& input)
{
	std::string line;

	this->clear();
	while (std::getline(input, line))
		this->_messages.push_back(line);
}

void MessageRegistry::clear()
{
	this->_messages.clear();
}
