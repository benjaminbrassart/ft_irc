/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 17:16:34 by bbrassar          #+#    #+#             */
/*   Updated: 2022/12/03 12:24:49 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include "class/ChannelManager.hpp"
# include "class/ClientManager.hpp"
# include "class/NicknameManager.hpp"
# include "class/ConnectionManager.hpp"
# include "class/exception/IOException.hpp"

# include "Channel.hpp"
# include "CommandMap.hpp"
# include "Logger.hpp"
# include "OperatorEntry.hpp"
# include "Recipient.hpp"

# include <netinet/in.h>
# include <poll.h>

# include <vector>

class Channel;
class ClientManager;
class NicknameManager;
class ChannelManager;
class ConnectionManager;
class CommandRegistry;
class Logger;

class Server {

	public:
		Server();
		~Server();

		typedef std::vector< pollfd > PollFdList;
		typedef std::vector< OperatorEntry > OperatorPasswordList;

		void		__socket(int port);
		void		__poll();
		void		loadOperatorFile(std::string const& file);

		Recipient*	getRecipient(std::string const& identifier);

		int sockFd;
		std::string startDate;
		std::string password;
		OperatorPasswordList operatorPasswords;

		// managers
		CommandMap commandMap;
		NicknameManager nickManager;
		ClientManager clientManager;
		ChannelManager channelManager;
		ConnectionManager connectionManager;
		Logger logger;

	private:
		PollFdList	_pollFds;
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
