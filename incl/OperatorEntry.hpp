/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OperatorEntry.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 11:09:39 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/21 11:38:43 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERATORENTRY_HPP
# define OPERATORENTRY_HPP

# include <string>

struct OperatorEntry
{
	std::string name;
	std::string host;
	std::string password;

	OperatorEntry();
	OperatorEntry(std::string const& name, std::string const& host, std::string const& password);
	OperatorEntry(OperatorEntry const& rhs);
	OperatorEntry& operator=(OperatorEntry const& rhs);
	~OperatorEntry();
};

#endif // OPERATORENTRY_HPP
