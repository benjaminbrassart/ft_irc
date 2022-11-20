/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 01:48:21 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/19 02:37:22 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"
#include <algorithm>

static bool __wildcardMatch(std::string const& pattern, std::string const& str)
{
	std::string::const_reverse_iterator pat;
	std::string::const_reverse_iterator s;

	for (pat = pattern.rbegin(), s = str.rbegin(); pat != pattern.rend(); ++pat, ++s)
	{
		if (*pat == '*')
		{
			if (++pat == pattern.rend())
				return true;
			while (s != str.rend() && *s != *pat)
				++s;
		}
		if (!(*pat == '?' || *s == *pat))
			return false;
	}
	return (s == str.rend() && pat == pattern.rend());
}

bool wildcardMatch(std::string const& pattern, std::string const& str)
{
	std::string rPattern = pattern;
	std::string rStr = str;

	std::reverse(rPattern.begin(), rPattern.end());
	std::reverse(rStr.begin(), rStr.end());

	// TODO it works but we should find something for elegant
	return __wildcardMatch(pattern, str) || __wildcardMatch(rPattern, rStr);
}
