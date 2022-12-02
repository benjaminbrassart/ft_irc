/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 17:16:34 by bbrassar          #+#    #+#             */
/*   Updated: 2022/12/02 15:42:54 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include "class/NicknameManager.hpp"
# include "class/exception/IOException.hpp"
# include "Channel.hpp"
# include "Client.hpp"
# include "CommandMap.hpp"
# include "Logger.hpp"
# include "OperatorEntry.hpp"
# include "Recipient.hpp"

# include <netinet/in.h>
# include <poll.h>

# include <vector>

class Client;
class Channel;
class CommandRegistry;
class Logger;

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

		typedef std::vector< pollfd > PollFdList;
		typedef std::vector< Client > ClientList;
		typedef std::vector< Channel > ChannelList;
		typedef std::vector< OperatorEntry > OperatorPasswordList;

		const int	&getsocketfd() const;
		const PollFdList	&getclientfd() const;

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

		Recipient*	getRecipient(std::string const& identifier);

		std::string startDate;
		CommandMap commands;
		std::string name;
		std::string password;
		std::string motdFileName;
		ChannelList	channels;
		ClientList	clients;
		OperatorPasswordList operatorPasswords;
		Logger logger;

		// managers
		NicknameManager nickManager;

	private:
		int			_socketfd;
		PollFdList	_clientfd;
		PollFdList	_newConnections;

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
		 * @return true if the client closed the connection, false otherwise
		 */
		bool __readFromClient(int fd);

		/**
		 * Write data to the client (if buffer has data)
		 *
		 * @param fd the socket file descriptor of the client
		 */
		void __writeToClient(int fd);

		/**
		 * Kill all active connections
		 */
		void __shutdown();

		static std::string __getStartDate();
}; // class Server

std::ostream& operator<<(std::ostream& os, sockaddr_in& address);
std::string operator+(std::string const& str, int n);
std::string operator+(std::string const& str, sockaddr_in& addr);
std::string operator+(sockaddr_in& addr, std::string const& str);

#endif // SERVER_HPP
