/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:33:12 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/16 18:47:04 by bbrassar         ###   ########.fr       */
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

class Client
{
public:
	typedef std::vector< Channel* > ChannelList;
	struct Info
	{
		std::string username;
		std::string hostname;
		std::string realname;
	};

public:
	Server* server;
	int sock_fd;
	::in_addr address;
	optional< std::string > nickname;
	optional< Info > info;
	optional< std::string > password;
	bool is_op;
	bool is_logged;
	ChannelList channels;

public:
	Client();
	~Client();

public:
	void send(std::string const& command);
	void reply(Reply code, std::string const& message);
	void closeConnection();
}; // class Client

#endif // CLIENT_HPP
