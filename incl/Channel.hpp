/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estoffel <estoffel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:34:18 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/17 20:06:59 by estoffel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "Client.hpp"
# include "Server.hpp"

# include <string>
# include <set>

class Client;
class Server;

class Channel {

	public:
		Channel();
		Channel(std::string name, std::string passwd);
		Channel(Channel const &src);
		~Channel();

		Channel						&operator=(Channel const &rhs);

		void 						broadcast(std::string const &message);
		void 						addClient(Client &client);
		void 						removeClient(Client &client);
		bool 						hasClient(Client &client);

		Server						*server;
		typedef std::set<Client*> 	ClientList;

		ClientList					allClients;
		std::string					name;
		std::string					topic;
		std::string					passwd;
};

#endif
