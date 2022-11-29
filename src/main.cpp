/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 00:55:38 by estoffel          #+#    #+#             */
/*   Updated: 2022/11/29 12:36:52 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include "Client.hpp"
#include "Server.hpp"
#include <csignal>

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
static void __setupSignal();

//./ircserv <port> <password>
int	main(int ac, char **av) {

	long	port;
	Server	server;

	port = parsing_input(ac, av[1]);
	if (port == -1)
		return 1;
	try
	{
		__setupSignal();
		server.password = av[2];
		server.initCommands();
		server.create_socket(port);
	}
	catch (Server::IoException const& e)
	{
		std::cerr << "I/O error: " << e.what() << std::endl;
	}
	close(server.getsocketfd());
	// close(server.getclientfd());
	return 0;
}

static void __handleSignal(int sig)
{
	// Ignore signal, then reset to its default action
	std::signal(sig, SIG_DFL);
}

static void __setupSignal()
{
	// Install signal handlers
	std::signal(SIGINT, __handleSignal);
}

//void	dispatch(int fd);
