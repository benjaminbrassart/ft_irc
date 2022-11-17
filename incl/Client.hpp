/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:33:12 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/17 20:43:08 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

#include "Server.hpp"
#include "Channel.hpp"
#include "optional.hpp"
#include "reply.h"

#include <string>
#include <vector>

#include <netinet/in.h>

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
		void 					reply(Reply code, std::string const& message);
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
};

#endif
