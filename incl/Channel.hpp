/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:34:18 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/17 15:25:41 by bbrassar         ###   ########.fr       */
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
		void 			broadcast(std::string const &message);

		std::string name;
		Server			*server;
		std::string		topic;
		std::string		password;

	private:
		mutable ClientList		_clients; // TODO find another way because it kinda violates const contract

	public:
		/**
		 * Add a client to this channel's members
		 *
		 * @param client the client to add
		 * @return true if the client was not already present in the channel, false otherwise
		 */
		bool addClient(Client& client) const;

		/**
		 * Remove a client from this channel's members
		 *
		 * @param client the client to remove
		 * @return true if the client was present in the channel, false otherwise
		 */
		bool removeClient(Client& client) const;

		/**
		 * Check whether a client is a member of this channel
		 *
		 * @param client the client to check the presence of
		 * @return true if the client in inside this channel, false otherwise
		 */
		bool hasClient(Client& client) const;
};

#endif // CHANNEL_HPP
