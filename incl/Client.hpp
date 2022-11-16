/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:33:12 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/16 19:09:35 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include "Channel.hpp"
# include "Server.hpp"
# include "optional.hpp"
# include "reply.h"

# include <sstream>
# include <string>
# include <utility>
# include <vector>

# include <netinet/in.h>

class Channel;
class Server;

class Client {

	public:
		Client();
		Client(Client const &src);
		~Client();

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
