/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelMode.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 23:38:12 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/21 01:59:06 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNELMODE_HPP
# define CHANNELMODE_HPP

// boolean options
# define MODE_ANONYMOUS			(1 << 0) // mode +a
# define MODE_INVITE_ONLY		(1 << 1) // mode +i
# define MODE_MODERATED			(1 << 2) // mode +m
# define MODE_NO_OUTSIDE		(1 << 3) // mode +n
# define MODE_QUIET				(1 << 4) // mode +q
# define MODE_PRIVATE			(1 << 5) // mode +p
# define MODE_SECRET			(1 << 6) // mode +s
# define MODE_SERVER_REOP		(1 << 7) // mode +r
# define MODE_OPERATOR_TOPIC	(1 << 7) // mode +t

// privileges options
# define MODE_CHANNEL_CREATOR	(1 << 8) // mode +O
# define MODE_CHANNEL_OPERATOR	(1 << 9) // mode +o
# define MODE_CHANNEL_VOICE		(1 << 10) // mode +v

// parameter options
# define MODE_KEY				(1 << 11) // mode +k
# define MODE_LIMIT				(1 << 12) // mode +l

// mask options
# define MODE_BANMASK			(1 << 13) // mode +b
# define MODE_EXCEPTIONMASK		(1 << 14) // mode +e
# define MODE_INVITEMASK		(1 << 15) // mode +I

typedef int ChannelMode;

#endif // CHANNELMODE_HPP
