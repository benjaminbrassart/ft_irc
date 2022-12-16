/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:34:18 by bbrassar          #+#    #+#             */
/*   Updated: 2022/12/16 00:52:13 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "ChannelPrivilege.hpp"
# include "Client.hpp"
# include "Server.hpp"
# include "Recipient.hpp"

# include <map>
# include <string>
# include <set>
# include <vector>

class Client;
class Server;
class Recipient;

class Channel : public Recipient {

	public:
		Channel(Server* server);
		Channel(Server* server, std::string name = std::string(), std::string passwd = std::string());
		Channel(Channel const &src);
		~Channel();

		Channel						&operator=(Channel const &rhs);

		struct ClientPrivilege
		{
			Client* client;
			ChannelPrivilege privilege;
		};

		typedef std::vector< ClientPrivilege >	ClientList;
		typedef std::set< Client* > 			InviteList;
		typedef std::set< std::string >			MaskList;

		std::string const		name;
		std::string				topic;
		std::string				passwd;
		std::string				modes;
		bool					inviteMode;
		bool					keyMode;
		bool					usrLimitMode;
		unsigned int			userLimit;
		ClientList				allClients;
		InviteList				invitedClients;

		bool					empty() const;
	
		void					addChanModes(std::string newModes);
		void					removeChanModes(std::string byeModes);

		void					addClient(Client &newClient, ChannelPrivilege privilege);
		void					removeClient(Client &client);
		bool					hasClient(Client &client) const;
		ClientList::iterator	getClient(Client& client);

		void 					inviteClient(Client& client);
		bool 					isInvited(Client& client);
		void 					uninviteClient(Client& client);

		void					setPriv(std::string &nick, ChannelPrivilege privilege);
		int						getClientPriv(Client &client);

		// Recipient overloads
		std::string const& 		getIdentifier() const;
		void					sendMessage(Client& sender, std::string const& command, std::string const& message);
		//
};

#endif
