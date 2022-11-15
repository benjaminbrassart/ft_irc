/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandMap.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 18:38:48 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/15 20:10:12 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDMAP_HPP
# define COMMANDMAP_HPP

# include "Client.hpp"

# include "command.h"

# include <map>
# include <string>

namespace irc
{
class Client;

class CommandMap
{
public:
	typedef std::map< std::string const&, CommandHandler > map_type;

private:
	map_type _commands;

public:
	CommandMap(void);
	CommandMap(CommandMap const &x);
	CommandMap &operator=(CommandMap const &x);
	~CommandMap();

public:
	void put(std::string const& name, CommandHandler handler);
	void dispatch(Client& client, std::string const& name);
}; // class CommandMap
} // namespace irc

#endif // COMMANDMAP_HPP