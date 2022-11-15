/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 17:16:34 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/15 18:01:43 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include "Client.hpp"
# include "Channel.hpp"

# include <algorithm>
# include <string>
# include <vector>

namespace irc
{
class Client;
class Channel;

class Server
{
public:
	typedef std::vector< Client > ClientList;
	typedef std::vector< Channel > ChannelList;

private:
	ClientList _clients;
	ChannelList _channels;

void dispatch(Client* sender);
}; // class Server
} // namespace irc

#endif // SERVER_HPP
