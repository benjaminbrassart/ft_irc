/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:33:12 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/18 20:05:52 by bbrassar         ###   ########.fr       */
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

		void 					closeConnection();

		struct Info {
			std::string 		username;
			std::string 		hostname;
			std::string 		realname;
		};

		Server* 				server;
		ChannelList 			channels;
		optional< std::string > password;
		optional< Info >		info;
		int 					sock_fd;
		bool					isOpe;
		bool 					isLogged;
		std::string				nickname;
		::in_addr 				address;

	private:
		void __replyRaw(Reply code, std::string const& message);
};

# include "template/Client.tpp"

#endif
