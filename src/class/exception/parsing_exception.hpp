/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_exception.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 14:07:11 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/14 14:09:46 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdexcept>

namespace irc
{
class parsing_exception : public std::exception
{
private:
	char const* _what;

public:
	parsing_exception(char const* what) :
		_what(what)
	{}

	~parsing_exception() throw()
	{}

	char const* what() const throw()
	{
		return this->_what;
	}
};
} // namespace irc
