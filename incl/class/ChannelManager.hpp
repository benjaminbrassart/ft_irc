/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelManager.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 14:56:48 by bbrassar          #+#    #+#             */
/*   Updated: 2022/12/12 22:01:15 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <vector>

class Channel;

/**
 * A class that stores and manipulates channels
 */
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
	/**
	 * Get a channel by its name
	 *
	 * @param name the name of the channel
	 * @return an iterator to the channel if found, `end()` otherwise
	 */
	iterator getChannel(std::string const& name);

	/**
	 * Add a new channel
	 *
	 * @param channel the channel to add
	 * @return an iterator poiting to the newly added channel
	 */
	iterator addChannel(Channel const& channel);

	/**
	 * Remove a channel by its name
	 *
	 * @param channelName the name of the channel
	 * @return true if the channel was successfuly removed, false otherwise
	 */
	bool removeChannel(std::string const& channelName);

	/**
	 * Remove a channel that is known to exist
	 *
	 * @param channel an iterator to the channel
	 * @return true if the iterator is not `end()`, false otherwise
	 */
	bool removeChannel(iterator channel);

public:
	iterator begin();
	iterator end();

}; // class ChannelManager
