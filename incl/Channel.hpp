/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:34:18 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/22 16:01:25 by lrandria         ###   ########.fr       */
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
		Channel(Client &owner, std::string name);
		Channel(Client &owner, std::string name, std::string passwd);
		Channel(Channel const &src);
		~Channel();

		Channel						&operator=(Channel const &rhs);

		typedef std::set<Client*>	ClientList;
		typedef std::vector<bool>	ModeFlags;

		Server						*server;
		ClientList					allClients;
		ClientList					banned;
		ClientList					operators;

		private:
			std::string				_owner;
			std::string				_name;
			std::string				_topic;
			std::string				_passwd;
			std::string				_modes; //need to define them

		public:
			
		/* ===============================================================
								GETTERS-SETTERS
   		================================================================== */

			bool	setName(std::string name);
			bool	setChanModes(std::string modes);
			void	setTopic(std::string topic);
			void	setPasswd(std::string passwd);

		/* ===============================================================
								BASIC UTILITIES
   		================================================================== */
		
		/* returns true if client was not already present in list, false otherwise or if client is banned */
			bool 	addClient(ClientList &list, Client &client); 
		
		/* returns true if client was in list, false otherwise */
			bool 	removeClient(ClientList &list, Client &client);
		
		/* returns true if client is in list, false otherwise */
			bool 	hasClient(ClientList &list, Client &client) const;
		
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
