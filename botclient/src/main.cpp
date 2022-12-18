/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 07:57:48 by estoffel          #+#    #+#             */
/*   Updated: 2022/12/18 19:33:24 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bot.hpp"
#include "InputContext.hpp"
#include "MessageRegistry.hpp"

#include <algorithm>
#include <deque>
#include <fstream>
#include <iostream>
#include <map>
#include <string>

int	main(int ac, char **av) {

	Bot	Mee1;

	if (ac != 3) {
		std::cerr << "Wrong number of arguments" << std::endl;
		return 1;
	}
	try
	{
		Mee1.connectClient(av[1], av[2]);
	}
	catch(const std::exception& e)
	{
		std::cerr << "I/O error: " << e.what() << '\n';
		return 1;
	}
	return 0;
}
