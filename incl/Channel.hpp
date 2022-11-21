/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:34:18 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/21 08:08:30 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "ChannelMode.hpp"
# include "Client.hpp"
# include "Server.hpp"

# include <string>
# include <set>

class Client;
class Server;

class Channel {

	public:
		Channel();
		Channel(Server& server, std::string name = std::string(), std::string passwd = std::string());
		Channel(Channel const &src);
		~Channel();

		Channel						&operator=(Channel const &rhs);

		typedef std::set< Client* >		ClientList;
		typedef std::set< std::string >	MaskList;

		Server			*server;
		ChannelMode		mode;
		std::string		name;
		std::string		topic;
		std::string		passwd;
		unsigned int	userLimit;
		ClientList		allClients;
		MaskList		banMasks;
		MaskList		exceptionMasks;
		MaskList		invitationMasks;

		static ChannelMode const DEFAULT_MODE;

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

		bool addBanMask(std::string const& mask);
		bool removeBanMask(std::string const& mask);
		void displayBanMasks(Client& client);

		bool addExceptionMask(std::string const& mask);
		bool removeExceptionMask(std::string const& mask);
		void displayExceptionMasks(Client& client);

		bool addInvitationMask(std::string const& mask);
		bool removeInvitationMask(std::string const& mask);
		void displayInvitationMasks(Client& client);

		/**
		 * Send a message from a client to all other clients in this channel
		 *
		 * @param sender the sender of the message
		 * @param msg the message to send
		 */
		void broadcast(Client &sender, std::string const msg);
};

#endif
