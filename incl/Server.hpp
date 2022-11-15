/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estoffel <estoffel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 17:16:34 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/15 22:34:35 by estoffel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# define GREY "\033[0;30m"
# define RORED "\033[0;31m"
# define RED "\033[0;91m"
# define GREEN "\033[0;32m"
# define YELW "\033[0;33m"
# define BLUE "\033[0;34m"
# define PINK "\033[0;35m"
# define TURQ "\033[0;36m"
# define WHITE "\033[0;97m"
# define BWHITE "\033[1;97m"
# define LWHITE "\033[4;97m"
# define IWHITE "\033[3;97m"
# define END "\e[0m"

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

class Client;
class Channel;

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

	private:
		ClientList	_clients;
		ChannelList	_channels;
		int			_socketfd;

}; // class Server

#endif // SERVER_HPP
