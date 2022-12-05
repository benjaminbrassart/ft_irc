/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IOException.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 15:22:38 by bbrassar          #+#    #+#             */
/*   Updated: 2022/12/02 15:25:28 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdexcept>
#include <string>

class IOException : public std::exception
{
private:
	std::string _reason;

public:
	IOException(std::string const& syscallName, int errnum);
	~IOException() throw();

public:
	char const* what() const throw();
}; // class IOException
