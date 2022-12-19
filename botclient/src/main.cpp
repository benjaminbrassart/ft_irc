/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 07:57:48 by estoffel          #+#    #+#             */
/*   Updated: 2022/12/19 20:53:05 by bbrassar         ###   ########.fr       */
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
#include <unistd.h>

int	main(int ac, char **av) {

	if (ac != 4) {
		std::cerr << "Wrong number of arguments\n";
		return 1;
	}

	std::ifstream input;

	input.open("answers.txt");

	if (!input)
	{
		std::cerr << "Unable to read answer file.\n";
		return 1;
	}

	Bot Mee1;
	int status = 0;

	try
	{
		Mee1.messageRegistry.load(input);
		input.close();
		Mee1.connectClient(av[1], av[2]);
		Mee1.authenticate("FlexBot", av[3]);
		while (Mee1.alive)
			Mee1.receive();
	}
	catch(const std::exception& e)
	{
		std::cerr << "I/O error: " << e.what() << '\n';
		status = 1;
	}
	if (Mee1.clientFd != -1)
		::close(Mee1.clientFd);
	return status;
}
