/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IOException.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 15:24:19 by bbrassar          #+#    #+#             */
/*   Updated: 2022/12/02 15:27:18 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "class/exception/IOException.hpp"
#include <cstring>

IOException::IOException(std::string const& syscallName, int errnum) :
	_reason(syscallName + ": " + std::strerror(errnum))
{}

IOException::~IOException() throw()
{}

char const* IOException::what() const throw()
{
	return this->_reason.c_str();
}
