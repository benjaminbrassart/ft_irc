/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 18:40:51 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/16 01:22:49 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# include "Client.hpp"
# include <string>
# include <vector>

class Client;

typedef void (*CommandHandler)(Client& client, std::string const& prefix, std::string const& line);

void command_pass(Client& client);

#endif // COMMAND_H
