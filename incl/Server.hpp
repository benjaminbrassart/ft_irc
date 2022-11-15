/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 17:16:34 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/15 20:18:11 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include "Client.hpp"
# include "Channel.hpp"

# include <iostream>
# include <string>
# include <vector>
# include <algorithm>
# include "colours.h"

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

#endif // SERVER_HPP
