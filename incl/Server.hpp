/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 17:16:34 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/16 21:22:01 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include "Client.hpp"
# include "Channel.hpp"

# include <algorithm>
# include <string>
# include <vector>
# include <iostream>
# include <sys/types.h>
# include <sys/socket.h>
# include <sys/stat.h>
# include <arpa/inet.h>
# include <netinet/in.h>
# include <sys/epoll.h>
# include <fcntl.h>
# include <cstdlib>
# include <signal.h>
# include <netdb.h>
# include <unistd.h>
# include <cstring>

typedef	std::string		String;
typedef	unsigned int	uint;

#include "CommandMap.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "colours.h"


class Client;
class Channel;
class CommandRegistry;

class Server {

	public:
		Server();
		~Server();

		typedef std::vector< Client > ClientList;
		typedef std::vector< Channel > ChannelList;

		void	dispatch(Client* sender);
		bool	create_socket();

		class IoException : public std::exception {
			public:
				IoException(String const&, int);
				~IoException() throw();

				virtual const char*	what() const throw();

			private:
				String	_what;
		};
	public:
		CommandMap commands;
		std::string password;

	private:
		ClientList	_clients;
		ChannelList	_channels;
		int			_socketfd;

}; // class Server

#endif // SERVER_HPP
