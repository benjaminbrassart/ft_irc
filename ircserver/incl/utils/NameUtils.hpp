/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NameUtils.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 01:55:54 by bbrassar          #+#    #+#             */
/*   Updated: 2022/12/15 02:01:47 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NAMEUTILS_HPP
# define NAMEUTILS_HPP

# include "Client.hpp"
# include "Channel.hpp"
# include <vector>

namespace NameUtils
{
struct Request
{
	std::string name;
	Channel* channel;
};

typedef std::vector< Request > RequestList;

void showAllNames(Client& client);
void showNames(Client& client, RequestList& requests);
void showName(Client& client, Request& request);
}

#endif // NAMEUTILS_HPP
