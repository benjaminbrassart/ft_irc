/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:33:12 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/15 18:56:18 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include "Channel.hpp"
# include "Server.hpp"

# include <sstream>
# include <string>
# include <vector>

# include <netinet/in.h>

class Channel;
class Server;

class Client
{
public:
	typedef std::vector< Channel* > ChannelList;

public:
	Server* server;
	int sock_fd;
	::in_addr address;
	std::string nickname;
	std::string username;
	std::string hostname;
	std::string servername;
	std::string realname;
	bool is_op;
	std::string buffer;

private:
	ChannelList _channels;
}; // class Client

#endif // CLIENT_HPP
