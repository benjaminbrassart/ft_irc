/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 19:54:03 by lrandria          #+#    #+#             */
/*   Updated: 2022/11/21 19:54:26 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>

bool	hasNonAscii(std::string input) {

	for (int i = 0; input[i]; i++)
		if (isprint(input[i]) == 0)
			return (true);
	return (false);
}