/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelManager.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 14:56:48 by bbrassar          #+#    #+#             */
/*   Updated: 2022/12/02 18:03:18 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <vector>

class Channel;

class ChannelManager
{
public:
	typedef std::vector< Channel > container_type;
	typedef container_type::iterator iterator;
	typedef container_type::reverse_iterator reverse_iterator;

private:
	container_type _channels;

public:
	ChannelManager();
	~ChannelManager();

public:
	iterator getChannel(std::string const& name);
	iterator addChannel(Channel const& channel);
	bool removeChannel(std::string const& channelName);
	bool removeChannel(iterator channel);

public:
	iterator begin();
	iterator end();

}; // class ChannelManager
