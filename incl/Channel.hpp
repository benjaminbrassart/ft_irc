/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:34:18 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/19 03:37:17 by bbrassar         ###   ########.fr       */
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

		typedef std::set< Client* > ClientList;

		std::string		name;
		Server			*server;
		std::string		topic;
		std::string		passwd;

	private:
		ClientList		allClients;

	public:
		/**
		 * Add a client to this channel's members
		 *
		 * @param client the client to add
		 * @return true if the client was not already present in the channel, false otherwise
		 */
		bool addClient(Client& client);

		/**
		 * Remove a client from this channel's members
		 *
		 * @param client the client to remove
		 * @return true if the client was present in the channel, false otherwise
		 */
		bool removeClient(Client& client);

		/**
		 * Check whether a client is a member of this channel
		 *
		 * @param client the client to check the presence of
		 * @return true if the client in inside this channel, false otherwise
		 */
		bool hasClient(Client& client) const;

		/**
		 * Send a message from a client to all other clients in this channel
		 *
		 * @param sender the sender of the message
		 * @param msg the message to send
		 */
		void broadcast(Client &sender, std::string const msg);
};

#endif
