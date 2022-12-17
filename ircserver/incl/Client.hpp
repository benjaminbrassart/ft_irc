/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:33:12 by bbrassar          #+#    #+#             */
/*   Updated: 2022/12/14 22:31:30 by bbrassar         ###   ########.fr       */
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
		void					flushWriteBuffer();

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

		std::string const&		getIdentifier() const;
		void					sendMessage(Client& sender, std::string const& command, std::string const& message);

		// the channels this client has joined
		ChannelList 			channels;
		// the username of this client (may not change over time)
		std::string				username;
		// the hostname this client used to connect to the server
		std::string				hostname;
		// the real name of this client
		std::string				realname;
		// the file descriptor (socket) of this client
		int						sock_fd;
		// the nickname of this client (may change over time)
		std::string				nickname;
		// the raw address of this client
		::sockaddr_in			address;
		// the buffer where is stored whatever this client is sending to the server
		std::string				readBuffer;
		// the buffer wgere is stored whatever the server sends to this client
		std::string				writeBuffer;
		// the connection password supplied by this client, empty if none
		std::string				password;
		// whether the connection to this client should be closed or not
		bool					shouldClose;
		// whether client is visible or not in WHO / NAMES lists
		bool					isInvisible;

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
