/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estoffel <estoffel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 07:57:48 by estoffel          #+#    #+#             */
/*   Updated: 2022/12/19 20:30:17 by estoffel         ###   ########.fr       */
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

	try
	{
		Mee1.messageRegistry.load(input);
		Mee1.connectClient(av[1], av[2]);
		Mee1.authenticate(av[3]); // TODO use automation (argv, env, stdin...)
		while (Mee1.alive)
			Mee1.receive();
	}
	catch(const std::exception& e)
	{
		std::cerr << "I/O error: " << e.what() << '\n';
		return 1;
	}
	return 0;
}
