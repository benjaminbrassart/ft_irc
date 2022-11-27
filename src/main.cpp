/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estoffel <estoffel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 00:55:38 by estoffel          #+#    #+#             */
/*   Updated: 2022/11/22 20:46:59 by estoffel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include "Client.hpp"
#include "Server.hpp"

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

//./ircserv <port> <password>
int	main(int ac, char **av) {

	long	port;
	Server	server;

	port = parsing_input(ac, av[1]);
	if (port == -1)
		return 1;
	try
	{
		server.create_socket(port);
	}
	catch (Server::IoException const& e)
	{
		std::cerr << "I/O error: " << e.what() << std::endl;
	}
	close(server.getsocketfd());
	close(server.getclientfd());
	return 0;
}

//void	dispatch(int fd);
