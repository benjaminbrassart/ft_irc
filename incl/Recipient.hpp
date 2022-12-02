/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Recipient.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 09:26:25 by bbrassar          #+#    #+#             */
/*   Updated: 2022/12/02 16:12:04 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RECIPIENT_HPP
# define RECIPIENT_HPP

# include <string>

class Server;
class Client;

class Recipient
{
public:
	Server* server;

	Recipient(Server* server);
	virtual ~Recipient();

public:
	virtual std::string const& getIdentifier() const = 0;
	virtual void sendMessage(Client& sender, std::string const& message) = 0;
}; // class Recipient

#endif // RECIPIENT_HPP
