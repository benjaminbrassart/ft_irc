/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 07:57:33 by estoffel          #+#    #+#             */
/*   Updated: 2022/12/17 14:10:08 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bot.hpp"
#include "InputContext.hpp"
#include <cstring>
#include <iostream>

Bot::Bot() {}

Bot::Bot(Bot const& cpy) {
	(void)cpy;
}

Bot&	Bot::operator=(Bot const& asgn) {
	(void)asgn;
	return *this;
}

Bot::~Bot() {}

Bot::IOException::IOException(std::string const& syscallName, int errnum) :
	_reason(syscallName + ": " + std::strerror(errnum)) {}

Bot::IOException::~IOException() throw() {}

char const* Bot::IOException::what() const throw()
{
	return this->_reason.c_str();
}

void	Bot::connexionClient() {


}

void Bot::onError(InputContext& ctx)
{
	std::cerr << "Received error";
	if (!ctx.args.empty())
		std::cerr << ": " << ctx.args[0];
	std::cerr << '\n';
	(void)ctx;
}

void Bot::onJoin(InputContext& ctx)
{
	(void)ctx;
}

void Bot::onInvite(InputContext& ctx)
{
	if (ctx.args.size() < 3)
		return;

	(void)ctx;
}

void Bot::onPart(InputContext& ctx)
{
	(void)ctx;
}

void Bot::onMessage(InputContext& ctx)
{
	(void)ctx;
}
