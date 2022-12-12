/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 00:55:38 by estoffel          #+#    #+#             */
/*   Updated: 2022/12/05 15:49:40 by bbrassar         ###   ########.fr       */
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
#include <unistd.h>

static Logger* __logger;

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
	if (*buf != '\0')
	{
		std::cerr << "Port number is rubbish!" << std::endl;
		return -1;
	}
	return l;
}

static void __handleSignal(int sig);

//./ircserv <port> <password>
int	main(int ac, char **av) {

	long port;

	port = parsing_input(ac, av[1]);
	if (port == -1)
		return 1;

	Server server;

	__logger = &server.logger;
	server.logger.log(INFO, "Starting " SERVER_NAME " version " VERSION);
	server.loadOperatorFile("operators.txt");
	KEEP_RUNNING = true;
	server.password = av[2];

	std::signal(SIGINT, __handleSignal);
	server.logger.log(DEBUG, "Signal handlers setup");

	try
	{
		server.createSocket(port);
		server.start();
	}
	catch (IOException const& e)
	{
		server.logger.log(FATAL, std::string("I/O error: ") + e.what());
		close(server.sockFd);
		return 1;
	}
	close(server.sockFd);
	return 0;
}

static void __handleSignal(int sig)
{
	std::cout << "\b\b"; // remove ^C from terminal
	__logger->log(INFO, "Press Ctrl+C again to force shutdown");
	KEEP_RUNNING = false; // stop the server as soon as possible
	std::signal(sig, SIG_DFL); // reset signal handler
	__logger->log(DEBUG, "Reset signal handler");
}
