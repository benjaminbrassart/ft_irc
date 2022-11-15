/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_exception.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 13:46:22 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/14 14:18:17 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstring>
#include <stdexcept>

namespace irc
{
class io_exception : public std::exception
{
private:
	std::string _what;

public:
	io_exception(std::string const& syscall, int errnum) :
		_what(syscall + ": " + std::strerror(errnum))
	{}

	~io_exception() throw()
	{}

	char const* what() const throw()
	{
		return this->_what.c_str();
	}
};
} // namespace irc
