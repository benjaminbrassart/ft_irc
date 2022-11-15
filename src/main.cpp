/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estoffel <estoffel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 00:55:38 by estoffel          #+#    #+#             */
/*   Updated: 2022/11/15 20:06:49 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <cstdlib>
#include <signal.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <string>

int	parsing_input(int ac, char *str) {

	if (ac != 3) {
		std::cerr << "Wrong number of arguments -> \"./ircserv <port> <password>\"\n";
		return 1;
	}
	char	*buf;
	long	l = strtol(str, &buf, 10);
	if (l < 0 || l > 65535) {
		std::cerr << "Port number is out of range" << std::endl;
		return 1;
	}
	if (strcmp(buf, "\0")) {
		std::cerr << "Port number is rubbish!" << std::endl;
		return 1;
	}
	return 0;
}

//./ircserv <port> <password>
int	main(int ac, char **av) {

	if (parsing_input(ac, av[1]));
		return 1;
	int	socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_fd != 0) {
		std::cerr << "Error trying to create a socket" << std::endl;
		return -1;
	}
	return 0;
}

//void	dispatch(int fd);
