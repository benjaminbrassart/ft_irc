/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:33:12 by bbrassar          #+#    #+#             */
/*   Updated: 2022/12/02 17:22:58 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Server.hpp"
#include "Channel.hpp"
#include "Reply.hpp"
#include "ClientState.hpp"
#include "Recipient.hpp"
#include "Logger.hpp"

#include <ctime>
#include <string>
#include <netinet/in.h>
#include <set>

class Channel;
class Server;
class Recipient;
class Logger;

class Client : public Recipient {

	public:
		Client(Server* server = NULL);
		Client(Server* server, int fd, sockaddr_in& addr);
		Client(Client const &src);
		~Client();

		Client &operator=(Client const& src);

		typedef std::set<Channel*> ChannelList;

		void					send(std::string const& command);
		template< Reply reply >
		void 					reply();
		template< Reply reply >
		void 					reply(std::string const& param);
		template< Reply reply >
		void 					reply(std::string const& param1, std::string const& param2);
		template< Reply reply >
		void 					reply(std::string const& param1, std::string const& param2, std::string const& param3);

		/**
		 * Make this client client leave the server
		 *
		 * @param message the message to be displayed to other clients
		 */
		void					quit(std::string const& message);

		/**
		 * Send the server's Message Of The Day to this client
		 */
		void					sendMotd();

		/**
		 * Read data from the client's socket
		 *
		 * @return true if client closed the connection, false otherwise
		 * @warning make sure the file descriptor is polled AND ready!
		 */
		bool					readFrom();

		/**
		 * Write data to the client's socket
		 *
		 * @warning make sure the file descriptor is polled AND ready!
		 */
		void					writeTo();

		/**
		 * Attempt to log in the client, does nothing if the client is not
		 * ready to be logged in
		 */
		void					tryLogin();

		/**
		 * Close this client's socket
		 */
		void 					closeConnection();

		/**
		 * Check whether a state is set or not for this client
		 *
		 * @return true if the state is set, false otherwise
		 */
		bool					checkState(ClientState state);

		/**
		 * Set a state for this client
		 *
		 * @param state the state to set
		 */
		void					setState(ClientState state);

		std::string				asPrefix();

		std::string const& getIdentifier() const;
		void sendMessage(Client& sender, std::string const& message);

		ChannelList 			channels;
		std::string				username;
		std::string				hostname;
		std::string				realname;
		std::string				hostAddress;
		int						sock_fd;
		std::string				nickname;
		::sockaddr_in			address;
		std::string				readBuffer;
		std::string				writeBuffer;
		std::string				password;

	private:
		int _state;

		template< Reply code >
		void __replyRaw(std::string const& message);
		void __replyRaw(Reply code, std::string const& message);
		void __processReadBuffer();
		void __log(LogLevel level, std::string const& message);
};

bool operator==(Client const& lhs, Client const& rhs);
bool operator!=(Client const& lhs, Client const& rhs);

#include "template/Client.tpp"
