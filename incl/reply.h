/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reply.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 01:45:10 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/16 12:08:16 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REPLY_H
# define REPLY_H

enum Reply
{
	RPL_WELCOME = 1,

	ERR_UNKNOWNCOMMAND = 421,
	ERR_NEEDMOREPARAMS = 461,
	ERR_ALREADYREGISTRED = 462,

	// TODO
	ERR_BADCHANMASK = 0,
	ERR_BADCHANNELKEY = 0,
	ERR_CANNOTSENDTOCHAN = 0,
	ERR_CHANNELISFULL = 0,
	ERR_ERRONEUSNICKNAME = 0,
	ERR_INVITEONLYCHAN = 0,
	ERR_NICKCOLLISION = 0,
	ERR_NICKNAMEINUSE = 0,
	ERR_NONICKNAMEGIVEN = 0,
	ERR_NOOPERHOST = 0,
	ERR_NORECIPIENT = 0,
	ERR_NOSUCHCHANNEL = 0,
	ERR_NOSUCHNICK = 0,
	ERR_NOTEXTTOSEND = 0,
	ERR_NOTONCHANNEL = 0,
	ERR_NOTOPLEVEL = 0,
	ERR_PASSWDMISMATCH = 0,
	ERR_TOOMANYCHANNELS = 0,
	ERR_TOOMANYTARGETS = 0,
	ERR_WILDTOPLEVEL = 0,
	RPL_AWAY = 0,
	RPL_TOPIC = 0,
	RPL_YOUREOPER = 0,
}; // enum Reply

#endif // REPLY_H
