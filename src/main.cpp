/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 07:08:07 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/14 16:43:37 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "class/server.hpp"
#include "class/exception/io_exception.hpp"
#include "class/exception/parsing_exception.hpp"
#include "ft_irc.h"
#include "parser.h"
#include <cstdlib>
#include <iostream>
#include <signal.h>

bool RUNNING = false;

static void __setup_signal();

int main(int argc, char const* argv[])
{
	irc::server server;

	if (argc != 3)
	{
		std::cerr << "Expected 2 arguments, got " << (argc - 1) << '\n';
		return 1;
	}

	::__setup_signal();

	try
	{
		server = irc::server(irc::parse_port(argv[1]), argv[2]);

		server.start();
		return 0;
	}
	catch (irc::parsing_exception const& e)
	{
		std::cerr << "Parsing error: " << e.what() << '\n';
	}
	catch (irc::io_exception const& e)
	{
		std::cerr << "I/O error: " << e.what() << '\n';
	}
	catch (std::exception const& e)
	{
		std::cerr << "Error: " << e.what() << '\n';
	}
	return 1;
}

static void __handle_signal(int sig)
{
	::signal(sig, SIG_DFL);
	std::cout << "\nShutting down gracefully...\n";
	if (sig == SIGINT)
		std::cout << "\nPress ctrl+c again to force quit.\n";
}

static void __setup_signal()
{
	::signal(SIGINT, __handle_signal);
	::signal(SIGQUIT, __handle_signal);
}
