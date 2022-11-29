/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 17:16:34 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/29 14:17:37 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include "Client.hpp"
# include "Channel.hpp"
# include "Recipient.hpp"
# include "Logger.hpp"

# include <algorithm>
# include <string>
# include <vector>
# include <iostream>
# include <sys/types.h>
# include <sys/socket.h>
# include <sys/stat.h>
# include <arpa/inet.h>
# include <netinet/in.h>
# include <poll.h>
# include <fcntl.h>
# include <cstdlib>
# include <signal.h>
# include <netdb.h>
# include <unistd.h>
# include <stdio.h>
# include <cstring>
# include <errno.h>

# if defined(__APPLE__) || defined(__MACH__)
#  define SET_NON_BLOCKING(fd) ::fcntl(fd, F_SETFL, O_NONBLOCK);
# else
#  define SET_NON_BLOCKING(fd)
# endif

#include "OperatorEntry.hpp"
#include "CommandMap.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include "colours.h"

class Client;
class Channel;
class CommandRegistry;

//sort by socket file descriptor
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

		typedef std::vector< Client > ClientList;
		typedef std::vector< Channel > ChannelList;
		typedef std::set< std::string > NicknameList;
		typedef std::vector< OperatorEntry > OperatorPasswordList;

		const int	&getsocketfd() const;
		const std::vector<pollfd>	&getclientfd() const;

		void		shutdown();

		void		initCommands();
		void		__socket(int port);
		void		__poll();
		void		loadOperatorFile(std::string const& file);

		ChannelList::iterator getChannel(std::string const& channelName);

		/**
		 * Process a line and break it into a command, then execute it if possible
		 *
		 * @param client the client whom issued the command
		 * @param line the command line to process
		 */
		void		processCommand(Client& client, std::string const& line);

		Client*		getClient(int fd);
		Client*		getClient(std::string const& nickname);

		void		removeClient(Client& client);

		bool		addNickname(std::string const& nickname);
		bool		removeNickname(std::string const& nickname);
		bool		hasNickname(std::string const& nickname);

		Recipient*	getRecipient(std::string const& identifier);

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
				IoException(std::string const& syscallName, int errnum);
				~IoException() throw();

				virtual const char*	what() const throw();

			private:
				std::string	_what;
		};

		std::string startDate;
		CommandMap commands;
		std::string name;
		std::string password;
		std::string motdFileName;
		ChannelList	channels;
		ClientList	clients;
		NicknameList nicknames;
		OperatorPasswordList operatorPasswords;
		Logger logger;

	private:
		int					_socketfd;
		std::vector<pollfd>	_clientfd;
		std::vector<pollfd>	_newConnections;
		bool				_running;

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
		 * Write data to the client (if buffer has data)
		 *
		 * @param fd the socket file descriptor of the client
		 */
		void __writeToClient(int fd);

		static std::string __getStartDate();
}; // class Server

std::ostream& operator<<(std::ostream& os, sockaddr_in& address);

#endif // SERVER_HPP
