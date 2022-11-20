/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:34:18 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/21 00:17:20 by lrandria         ###   ########.fr       */
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

		Channel			&operator=(Channel const &rhs);

		typedef std::set< Client* > ClientList;

		Server				*server;
		std::string			name;
		std::string			topic;
		std::string			passwd;
		std::vector<char>	modes; //need to define them
		ClientList			allClients;
		ClientList			banned;
		ClientList			operators;

		/* returns true if client was not already present in list, false otherwise or if client is banned */
		bool 	addClient(ClientList list, Client& client); 
		
		/* returns true if client was in list, false otherwise */
		bool 	removeClient(ClientList list, Client& client);
		
		/* returns true if client is in list, false otherwise */
		bool 	hasClient(ClientList list, Client& client) const;
		
		/* Send a message from a client to all other clients in this channel */
		void 	broadcast(Client &sender, std::string const msg);

		/* Only operators can add modes */
		void	addModes(std::string modes);

		/* ===============================================================
								OPERATORS CMDS
   		================================================================== */

		void 	invite(Client &ope, Client &nick);
		void 	kick(Client &ope, Client &nick);
		// void oper(Client &ope, Client &nick);
		// void wallops(Client &ope, Client &nick);
		// void globops(Client &ope, Client &nick);
		// void chatops(Client &ope, Client &nick);
		// void adchat(Client &ope, Client &nick);
		// void nachat(Client &ope, Client &nick);






};

#endif
