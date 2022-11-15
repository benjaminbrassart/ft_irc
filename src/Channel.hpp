/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estoffel <estoffel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:34:18 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/15 19:10:45 by estoffel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "Client.hpp"
# include "Server.hpp"

# include <string>
# include <vector>

namespace irc
{
class Client;
class Server;

class Channel
{
public:
	typedef std::vector< Client* > ClientList;

public:
	Server* server;
	std::string topic;
	std::string password;
private:
	ClientList _clients;

public:
	void broadcast(std::string const& message);
};
} // namespace irc

#endif // CHANNEL_HPP
