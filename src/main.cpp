/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 00:55:38 by estoffel          #+#    #+#             */
/*   Updated: 2022/11/29 21:47:33 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include "Client.hpp"
#include "Reply.hpp"
#include "Server.hpp"
#include "Logger.hpp"
#include <csignal>

#include "wildcard.h"
#include "config.h"
#include "ft_irc.h"

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <algorithm>

volatile sig_atomic_t KEEP_RUNNING;

long	parsing_input(int ac, char *str) {

	if (ac != 3) {
		std::cerr << "Wrong number of arguments -> \"./ircserv <port> <password>\"\n";
		return -1;
	}
	char	*buf;
	long	l = strtol(str, &buf, 10);
	if (l < 0 || l > 65535) {
		std::cerr << "Port number is out of range" << std::endl;
		return -1;
	}
	if (strcmp(buf, "\0")) {
		std::cerr << "Port number is rubbish!" << std::endl;
		return -1;
	}
	return l;
}

static void __handleSignal(int sig);

//./ircserv <port> <password>
int	main(int ac, char **av) {

	Server	server;
	long	port;

	port = parsing_input(ac, av[1]);
	if (port == -1)
		return 1;

	server.logger.log(INFO, "Starting " + server.name + " version " + VERSION);
	server.logger.log(INFO, std::string("Build date ") + STR(BUILD_DATE));

	server.name = "ft_ble";
	server.motdFileName = "motd.txt";

	server.loadOperatorFile("operators.txt");

	KEEP_RUNNING = true;

	server.password = av[2];
	server.initCommands();

	std::signal(SIGINT, __handleSignal);
	server.logger.log(DEBUG, "Signal handlers setup");

	try
	{
		server.__socket(port);
	}
	catch (Server::IoException const& e)
	{
		server.logger.log(ERROR, std::string("I/O error: ") + e.what());
		// std::cerr << "I/O error: " << e.what() << std::endl;
	}
	close(server.getsocketfd());
	return 0;
}

static void __handleSignal(int sig)
{
	std::cout << '\n' << "Press Ctrl+C again to force shutdown." << '\n';
	KEEP_RUNNING = false;
	// Ignore signal, then reset to its default action
	std::signal(sig, SIG_DFL);
}
