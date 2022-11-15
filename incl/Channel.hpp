/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estoffel <estoffel@student.42.fr>          +#+  +:+       +#+        */
/*   Updated: 2022/11/15 20:07:28 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "Client.hpp"
# include "Server.hpp"

# include <string>
# include <vector>

class Client;
class Server;

class Channel {

	public:
		Channel();
		~Channel();

		typedef std::vector<Client*> ClientList;
		
		void			cmdJoin(std::string channel, std::string key);
		void			cmdPart(std::string channel, std::string reason);
		void			cmdTopic(std::string channel, std::string topic);
		void			cmdNames(std::string channel);
		void			cmdList(std::string channel); // optional "elist" param
		void			cmdInvite(std::string nickname, std::string channel);
		void			cmdKick(std::string channel, std::string user);
		//Server Queries and Commands
		// void			cmdMOTD(std::string target);
		// void			cmdAdmin(std::string target);
		// int				cmdLusers(); // returns stats about local/global users
		// void			cmdTime(std::string server);
		// void			cmdStats(std::string query, std::string server);
		// void			cmdHelp(std::string subject);
		// void			cmdInfo();
		// void			cmdMode(std::string target); //check the other params
		void 			broadcast(std::string const &message);

		Server			*server;
		std::string		topic;
		std::string		password;
	
	private:
		ClientList		_clients;
};

#endif // CHANNEL_HPP
