/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 17:16:34 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/21 08:22:22 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include "Client.hpp"
# include "Channel.hpp"

# include <algorithm>
# include <string>
# include <vector>
# include <iostream>
# include <sys/types.h>
# include <sys/socket.h>
# include <sys/stat.h>
# include <arpa/inet.h>
# include <netinet/in.h>
# include <sys/epoll.h>
# include <fcntl.h>
# include <cstdlib>
# include <signal.h>
# include <netdb.h>
# include <unistd.h>
# include <stdio.h>
# include <cstring>

# if defined(__APPLE__) || defined(__MACH__)
#  define SET_NON_BLOCKING(fd) ::fcntl(fd, F_SETFL, O_NONBLOCK);
# else
#  define SET_NON_BLOCKING(fd)
# endif

using					std::string;

#include "CommandMap.hpp"
#include <iostream>
#include <string>
#include <set>
#include <algorithm>
#include "colours.h"

class Client;
class Channel;
class CommandRegistry;

// sort by socket file descriptor
struct ClientComparator : public std::binary_function< Client, Client, bool >
{
	bool operator()(Client const& lhs, Client const& rhs) const;
};

// sort by channel name
struct ChannelComparator : public std::binary_function< Channel, Channel, bool >
{
	bool operator()(Channel const& rhs, Channel const& lhs) const;
};

class Server {

	public:
		Server();
		~Server();

		typedef std::set< Client, ClientComparator > ClientList;
		typedef std::set< Channel, ChannelComparator > ChannelList;
		typedef std::map< std::string, std::string > OperatorPasswordMap;

		const int	&getsocketfd() const;
		const int	&getclientfd() const;

		void		create_socket(int port);
		void		loadOperatorFile(std::string const& file);

		Channel*	getChannel(std::string const& channelName);
		Channel&	getOrCreateChannel(std::string const& channelName);

		/**
		 * Process a line and break it into a command, then execute it if possible
		 *
		 * @param client the client whom issued the command
		 * @param line the command line to process
		 */
		void		processCommand(Client& client, std::string const& line);

		class IoException : public std::exception {
			public:
				/**
				 * Construct a new IoException
				 *
				 * @param syscallName the name of the system call that failed
				 * @param errnum the code of the error
				 * @see errno(3)
				 * @see strerror(3)
				 */
				IoException(string const& syscallName, int errnum);
				~IoException() throw();

				virtual const char*	what() const throw();

			private:
				string	_what;
		};

		CommandMap commands;
		std::string name;
		std::string password;
		std::string motdFileName;
		ChannelList	channels;
		ClientList	clients;
		OperatorPasswordMap operatorPasswords;

	private:
		int			_socketfd;
		int			_clientfd;

		/**
		 * Accept a client and add it to the client list
		 *
		 * @see accept(2)
		 */
		void __acceptClient();

		/**
		 * Read data from a polled client
		 *
		 * @param fd the socket file descriptor of the client
		 */
		void __readFromClient(int fd);

		/**
		 * Write data to the client (if any)
		 *
		 * @param fd the socket file descriptor of the client
		 */
		void __writeToClient(int fd);

}; // class Server

#endif // SERVER_HPP
