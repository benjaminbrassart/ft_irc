/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optional.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 10:56:27 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/16 11:33:26 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPTIONAL_HPP
# define OPTIONAL_HPP

template< class T >
struct optional
{
	T value;
	bool has_value;

	optional();
	optional(T const& val);
	optional(optional const& x);
	optional& operator=(optional const& x);
	~optional();

	operator bool();
	bool operator==(T const& rhs);
	bool operator==(optional const& rhs);
};

template< class T >
optional< T > make_optional();

template< class T >
optional< T > make_optional(T const& value);

#include "template/optional.tpp"

#endif // OPTIONAL_HPP
