/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:34:18 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/22 17:40:24 by lrandria         ###   ########.fr       */
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

		Server				*server;
		ChannelMode			mode;
		std::string const	name;
		std::string			topic;
		std::string			passwd;
		unsigned int		userLimit;
		ClientList			allClients;
		MaskList			banMasks;
		MaskList			exceptionMasks;
		MaskList			invitationMasks;

		static ChannelMode const DEFAULT_MODE;




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
