/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optional.tpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 11:14:44 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/16 11:18:36 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

template< class T >
struct optional;

template< class T >
optional< T >::optional() :
	value(),
	has_value(false)
{}

template< class T >
optional< T >::optional(T const& val) :
	value(val),
	has_value(true)
{}

template< class T >
optional< T >::optional(optional const& x) :
	value(x.value),
	has_value(x.has_value)
{}

template< class T >
optional< T >& optional< T >::operator=(optional const& x)
{
	this->value = x.value;
	this->has_value = x.has_value;
	return *this;
}

template< class T >
optional< T >::~optional()
{
}

template< class T >
optional< T >::operator bool()
{
	return this->has_value;
}

template< class T >
optional< T > make_optional()
{
	return optional< T >();
}

template< class T >
optional< T > make_optional(T const& value)
{
	return optional< T >(value);
}
