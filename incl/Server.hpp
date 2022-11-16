/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estoffel <estoffel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 17:16:34 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/16 20:41:58 by estoffel         ###   ########.fr       */
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
# include <stdio.h>
# include <cstring>

using					std::string;
typedef	unsigned int	uint;

# include "Client.hpp"
# include "Channel.hpp"

# include <iostream>
# include <string>
# include <vector>
# include <algorithm>
# include "colours.h"

class Client;
class Channel;

class Server {

	public:
		Server();
		~Server();

		typedef std::vector< Client > ClientList;
		typedef std::vector< Channel > ChannelList;

		const int	&getsocketfd() const;
		const int	&getclientfd() const;
		
		void	dispatch(Client* sender);
		void	create_socket(int port);

		class IoException : public std::exception {
			public:
				IoException(string const&, int);
				~IoException() throw();

				virtual const char*	what() const throw();

			private:
				string	_what;
		};

	private:
		ClientList	_clients;
		ChannelList	_channels;
		int			_socketfd;
		int			_clientfd;

}; // class Server

#endif // SERVER_HPP
