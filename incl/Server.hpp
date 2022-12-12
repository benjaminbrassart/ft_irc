/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 17:16:34 by bbrassar          #+#    #+#             */
/*   Updated: 2022/12/12 22:49:16 by bbrassar         ###   ########.fr       */
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

		typedef std::vector< OperatorEntry > OperatorPasswordList;

		void		createSocket(int port);
		void		start();
		void		loadOperatorFile(std::string const& file);

		void		sendMotd(Client& client);

		Recipient*	getRecipient(std::string const& identifier);

		Logger logger;

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

	private:

		/**
		 * Kill all active connections
		 */
		void __shutdown();

		/**
		 * Wrapper function for C's strftime
		 *
		 * @note format: '%Y-%m-%d %H:%M:%S'
		 * @return a string that contains the current date
		 */
		static std::string __getStartDate();
}; // class Server

std::ostream& operator<<(std::ostream& os, sockaddr_in& address);
std::string operator+(std::string const& str, int n);
std::string operator+(std::string const& str, sockaddr_in& addr);
std::string operator+(sockaddr_in& addr, std::string const& str);

#endif // SERVER_HPP
