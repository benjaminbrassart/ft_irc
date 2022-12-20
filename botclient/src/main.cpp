/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parallels <parallels@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 07:57:48 by estoffel          #+#    #+#             */
/*   Updated: 2022/12/20 04:21:04 by parallels        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bot.hpp"
#include "InputContext.hpp"
#include "MessageRegistry.hpp"

#include <algorithm>
#include <csignal>
#include <deque>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <unistd.h>

static Bot* botPtr;

static void __handleSignal(int sig);

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

	Bot mee1;
	int status = 0;

	botPtr = &mee1;

	try
	{
		mee1.messageRegistry.load(input);
		input.close();

		struct sigaction sa = {};

		sa.sa_handler = __handleSignal;
		::sigemptyset(&sa.sa_mask);
		::sigaction(SIGINT, &sa, NULL);

		mee1.connectClient(av[1], av[2]);
		mee1.authenticate("Mee1", av[3]);
		while (mee1.alive)
			mee1.receive();
	}
	catch(const std::exception& e)
	{
		std::cerr << "I/O error: " << e.what() << '\n';
		status = 1;
	}
	if (mee1.clientFd != -1)
		::close(mee1.clientFd);
	return status;
}

static void __handleSignal(int sig)
{
	std::signal(sig, SIG_DFL);
	botPtr->alive = false;
}
