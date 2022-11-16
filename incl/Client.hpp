/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:33:12 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/16 01:37:32 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include "Channel.hpp"
# include "Server.hpp"

# include <sstream>
# include <string>
# include <utility>
# include <vector>

# include <netinet/in.h>

class Channel;
class Server;

struct ClientInfo
{
	std::string username;
	std::string hostname;
	std::string realname;
}; // struct ClientInfo

class Client
{
public:
	typedef std::vector< Channel* > ChannelList;

public:
	Server* server;
	int sock_fd;
	::in_addr address;
	std::pair< std::string, bool > nickname;
	std::pair< ClientInfo, bool > info;
	std::pair< std::string, bool > password;
	bool is_op;
	std::string buffer;
	bool is_logged;

public:
	Client();
	~Client();

private:
	ChannelList _channels;

public:
	void reply(int code, std::string const& message);
}; // class Client

#endif // CLIENT_HPP
