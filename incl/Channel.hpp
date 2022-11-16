/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:34:18 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/16 18:53:43 by lrandria         ###   ########.fr       */
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

	private:
		ClientList					_clients;
		std::string					_name;
		std::string					_topic;
		std::string					_passwd;
};

#endif
