/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 14:00:29 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/14 17:12:23 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "class/exception/parsing_exception.hpp"
#include "parser.h"
#include <cctype>
#include <limits>

::uint16_t irc::parse_port(char const* s)
{
	static std::numeric_limits< uint16_t > LIM;
	::uint32_t n;

	n = 0;
	while (std::isdigit(*s))
	{
		n = n * 10 + *s - '0';
		if (n > LIM.max())
			break;
		++s;
	}

	if (*s != '\0')
		throw irc::parsing_exception("port");

	return static_cast<uint16_t>(n);
}

::in_addr_t irc::parse_address(char const* s)
{
	int res;
	in_addr addr;

	res = ::inet_aton(s, &addr);
	if (res == 0)
		throw irc::parsing_exception("address");
	return addr.s_addr;
}
