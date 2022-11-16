/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:34:18 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/16 14:00:07 by bbrassar         ###   ########.fr       */
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
		Channel(int test); // which params do I need?
		~Channel();

		typedef std::vector<Client*> ClientList;

		void 			broadcast(std::string const &message);

		Server			*server;
		std::string		topic;
		std::string		password;

	private:
		ClientList		_clients;

	public:
		void addClient(Client& client);
		void removeClient(Client& client);
		bool hasClient(Client& client);
};

#endif // CHANNEL_HPP
