/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:33:12 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/19 04:13:44 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include "Server.hpp"
# include "Channel.hpp"
# include "Reply.hpp"
# include "ClientState.hpp"

# include <string>
# include <vector>

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

		typedef std::vector<Channel*> ChannelList;

		void					send(std::string const& command);
		template< Reply reply >
		void 					reply();
		template< Reply reply >
		void 					reply(std::string const& param);
		template< Reply reply >
		void 					reply(std::string const& param1, std::string const& param2);
		template< Reply reply >
		void 					reply(std::string const& param1, std::string const& param2, std::string const& param3);

		void					quit(std::string const& message);

		void					sendMotd();

		void					readFrom();
		void					writeTo();

		void					tryLogin();
		void 					closeConnection();

		bool					checkState(ClientState state);
		void					setState(ClientState state);

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
