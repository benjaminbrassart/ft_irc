/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientState.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 04:13:07 by bbrassar          #+#    #+#             */
/*   Updated: 2022/12/13 06:00:03 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_STATE_HPP
# define CLIENT_STATE_HPP

enum ClientState
{
	CLIENT_STATE_INIT = 0,
	CLIENT_STATE_USER = 1 << 1,
	CLIENT_STATE_NICK = 1 << 2,
	CLIENT_STATE_OPERATOR = 1 << 3,
	CLIENT_STATE_LOGGED = (CLIENT_STATE_USER | CLIENT_STATE_NICK),
	CLIENT_STATE_NICK_FAILED = 1 << 4,
}; // enum ClientState

#endif // CLIENT_STATE_HPP
