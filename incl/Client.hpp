/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:33:12 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/21 09:17:28 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include "Server.hpp"
# include "Channel.hpp"
# include "Reply.hpp"
# include "ClientState.hpp"

# include <string>
# include <set>

# include <netinet/in.h>

class Channel;
class Server;

class Client {

	public:
		Client(Server& server);
		Client(Server& server, int fd, sockaddr_in& addr);
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
		 * @warning make sure the file descriptor is polled AND ready!
		 */
		void					readFrom();

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

		/**
		 * Make this user leave a channel
		 *
		 * @param channel the channel to leave
		 * @param message the message to be displayed to other clients
		 */
		void					leaveChannel(Channel& channel, std::string const& message);

		/**
		 * Make this user leave all joined channels
		 *
		 * @param message the message to be displayed to other clients
		 */
		void					leaveAllChannels(std::string const& message);

		struct Info {
			std::string 		username;
			std::string 		hostname;
			std::string 		realname;
		};

		Server* 				server;
		ChannelList 			channels;
		Info					info;
		int 					sock_fd;
		std::string				nickname;
		::sockaddr_in			address;
		std::string				readBuffer;
		std::string				writeBuffer;

		static int const READ_BUFFER_SIZE;

	private:
		int _state;

		void __replyRaw(Reply code, std::string const& message);
		void __processReadBuffer();
};

# include "template/Client.tpp"

#endif
