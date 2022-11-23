/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 01:48:21 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/21 00:49:28 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"
#include <algorithm>

bool wildcardMatch(std::string const& pattern, std::string const& str)
{
	std::string::const_reverse_iterator pat;
	std::string::const_reverse_iterator s;

	for (pat = pattern.rbegin(), s = str.rbegin(); pat != pattern.rend(); ++pat, ++s)
	{
		if (*pat == '*')
		{
			do
			{
				++pat;
			}
			while (pat != pattern.rend() && (*pat == '*' || (s != str.rend() && *pat == '?')));

			if (pat == pattern.rend())
				return true;
			while (s != str.rend() && *s != *pat)
				++s;
		}
		if (!(*pat == '?' || *s == *pat))
			return false;
	}
	return (s == str.rend() && pat == pattern.rend());
}
