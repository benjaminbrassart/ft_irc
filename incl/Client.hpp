/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:33:12 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/18 22:31:19 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include "Server.hpp"
# include "Channel.hpp"
# include "optional.hpp"
# include "reply.h"

# include <string>
# include <vector>

# include <netinet/in.h>

class Channel;
class Server;

class Client {

	public:
		Client();
		Client(Client const &src);
		Client(int fd, sockaddr_in& addr);
		~Client();

		Client &operator=(Client const& src);

		typedef std::vector<Channel*> ChannelList;

		void 					send(std::string const& command);
		template< Reply reply >
		void 					reply();
		template< Reply reply >
		void 					reply(std::string const& param);
		template< Reply reply >
		void 					reply(std::string const& param1, std::string const& param2);
		template< Reply reply >
		void 					reply(std::string const& param1, std::string const& param2, std::string const& param3);

		void					readFrom();
		void					writeTo();

		void 					closeConnection();

		struct Info {
			std::string 		username;
			std::string 		hostname;
			std::string 		realname;
		};

		Server* 				server;
		ChannelList 			channels;
		optional< std::string >	password;
		optional< Info >		info;
		int 					sock_fd;
		bool					isOpe;
		bool 					isLogged;
		std::string				nickname;
		::sockaddr_in			address;
		std::string				readBuffer;
		std::string				writeBuffer;

		static int const READ_BUFFER_SIZE;

	private:
		void __replyRaw(Reply code, std::string const& message);
		void __processReadBuffer();
};

# include "template/Client.tpp"

#endif
