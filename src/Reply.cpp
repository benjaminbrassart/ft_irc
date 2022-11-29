/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Reply.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 18:04:40 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/29 12:56:12 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Reply.hpp"
#include "config.h"

std::string ReplyFactory<RPL_WELCOME>::makeReply(std::string const& nickname, std::string const& username, std::string const& hostname)
{
	return nickname + " Welcome to the Internet Relay Network " + nickname + '!' + username + '@' + hostname;
}

std::string ReplyFactory<RPL_YOURHOST>::makeReply(std::string const& nickname)
{
	return nickname + " Your host is " SERVER_NAME ", running version " VERSION;
};

std::string ReplyFactory<RPL_CREATED>::makeReply(std::string const& nickname, std::string const& startDate)
{
	return nickname + " This server was created " + startDate;
};

std::string ReplyFactory<RPL_MYINFO>::makeReply(std::string const& nickname, std::string const& serverName)
{
	return nickname + " " + serverName + " " VERSION " o O"; // TODO add channel modes
};

std::string ReplyFactory<RPL_LIST>::makeReply(std::string const& channel, std::string const& visibleClients, std::string const& topic)
{
	return channel + " " + visibleClients + " :" + topic;
}

std::string ReplyFactory<RPL_LISTEND>::makeReply()
{
	return ":End of LIST";
}

std::string ReplyFactory<RPL_CHANNELMODEIS>::makeReply(std::string const& channel, std::string const& mode, std::string const& params)
{
	return channel + " " + mode + " " + params;
}

std::string ReplyFactory<RPL_UNIQOPIS>::makeReply(std::string const& channel, std::string const& nickname)
{
	return channel + " " + nickname;
}

std::string ReplyFactory<RPL_NOTOPIC>::makeReply(std::string const& channel)
{
	return channel + " :No topic is set";
}

std::string ReplyFactory<RPL_TOPIC>::makeReply(std::string const& channel, std::string const& topic)
{
	return channel + " :" + topic;
}

std::string ReplyFactory<RPL_MOTD>::makeReply(std::string const& text)
{
	return ":- " + text;
}

std::string ReplyFactory<RPL_MOTDSTART>::makeReply(std::string const& serverName)
{
	return ":- " + serverName + " Message of the day -";
}

std::string ReplyFactory<RPL_ENDOFMOTD>::makeReply()
{
	return ":End of MOTD command";
}

std::string ReplyFactory<RPL_YOUREOPER>::makeReply()
{
	return ":You are now an IRC operator";
}

std::string ReplyFactory<ERR_NOSUCHNICK>::makeReply(std::string const& nickname)
{
	return nickname + " :No such nick/channel";
}

std::string ReplyFactory<ERR_NOSUCHCHANNEL>::makeReply(std::string const& channel)
{
	return channel + " :No such channel";
}

std::string ReplyFactory<ERR_CANNOTSENDTOCHAN>::makeReply(std::string const& channel)
{
	return channel + " :Cannot send to channel";
}

std::string ReplyFactory<ERR_TOOMANYCHANNELS>::makeReply(std::string const& channel)
{
	return channel + " :You have joined too many channels";
}

std::string ReplyFactory<ERR_TOOMANYTARGETS>::makeReply(std::string const& target, std::string const& errorCode, std::string const& abortMessage)
{
	return target + " :" + errorCode + " recipients. " + abortMessage;
}

std::string ReplyFactory<ERR_NOORIGIN>::makeReply()
{
	return ":No origin specified";
}

std::string ReplyFactory<ERR_NOTEXTTOSEND>::makeReply()
{
	return ":No text to send";
}

std::string ReplyFactory<ERR_NOTOPLEVEL>::makeReply()
{
	return ":No toplevel domain specified";
}

std::string ReplyFactory<ERR_WILDTOPLEVEL>::makeReply(std::string const& mask)
{
	return mask + " :Wildcard in toplevel domain";
}

std::string ReplyFactory<ERR_BADMASK>::makeReply(std::string const& mask)
{
	return mask + " :Bad Server/host mask";
}

std::string ReplyFactory<ERR_UNKNOWNCOMMAND>::makeReply(std::string const& command)
{
	return command + " :Unknown command";
}

std::string ReplyFactory<ERR_NOMOTD>::makeReply()
{
	return ":MOTD File is missing";
}

std::string ReplyFactory<ERR_FILEERROR>::makeReply(std::string const& operation, std::string const& name)
{
	return ":File error doing " + operation + " on " + name;
}

std::string ReplyFactory<ERR_NONICKNAMEGIVEN>::makeReply()
{
	return ":No nickname given";
}

std::string ReplyFactory<ERR_ERRONEUSNICKNAME>::makeReply(std::string const& nickname)
{
	return nickname + " :Erroneous nickname";
}

std::string ReplyFactory<ERR_NICKNAMEINUSE>::makeReply(std::string const& nickname)
{
	return nickname + " :Nickname is already in use";
}

std::string ReplyFactory<ERR_UNAVAILRESOURCE>::makeReply(std::string const& resource)
{
	return resource + " :Nick/channel is temporarily unavailable";
}

std::string ReplyFactory<ERR_USERNOTINCHANNEL>::makeReply(std::string const& nickname, std::string const& channel)
{
	return nickname + " " + channel + " :They aren't on that channel";
}

std::string ReplyFactory<ERR_NOTONCHANNEL>::makeReply(std::string const& channel)
{
	return channel + " :You're not on that channel";
}

std::string ReplyFactory<ERR_USERONCHANNEL>::makeReply(std::string const& user, std::string const& channel)
{
	return user + " " + channel + " :is already on channel";
}

std::string ReplyFactory<ERR_NOLOGIN>::makeReply(std::string const& user)
{
	return user + " :User not logged in";
}

std::string ReplyFactory<ERR_SUMMONDISABLED>::makeReply()
{
	return ":SUMMON has been disabled";
}

std::string ReplyFactory<ERR_USERSDISABLED>::makeReply()
{
	return ":USERS has been disabled";
}

std::string ReplyFactory<ERR_NEEDMOREPARAMS>::makeReply(std::string const& command)
{
	return command + " :Not enough parameters";
}

std::string ReplyFactory<ERR_ALREADYREGISTRED>::makeReply()
{
	return ":Unauthorized command (already registered)";
}

std::string ReplyFactory<ERR_NOPERMFORHOST>::makeReply()
{
	return ":Your host isn't among the privileged";
}

std::string ReplyFactory<ERR_PASSWDMISMATCH>::makeReply()
{
	return ":Password incorrect";
}

std::string ReplyFactory<ERR_YOUREBANNEDCREEP>::makeReply()
{
	return ":You are banned from this server";
}

std::string ReplyFactory<ERR_YOUWILLBEBANNED>::makeReply()
{
	return ""; // TODO
}


std::string ReplyFactory<ERR_KEYSET>::makeReply(std::string const& channel)
{
	return channel + " :Channel key already set";
}

std::string ReplyFactory<ERR_CHANNELISFULL>::makeReply(std::string const& channel)
{
	return channel + " :Cannot join channel (+l)";
}

std::string ReplyFactory<ERR_UNKNOWNMODE>::makeReply(std::string const& c, std::string const& channel)
{
	return c + " :is unknown mode char to me for " + channel;
}

std::string ReplyFactory<ERR_INVITEONLYCHAN>::makeReply(std::string const& channel)
{
	return channel + " :Cannot join channel (+i)";
}

std::string ReplyFactory<ERR_BANNEDFROMCHAN>::makeReply(std::string const& channel)
{
	return channel + " :Cannot join channel (+b)";
}

std::string ReplyFactory<ERR_BADCHANNELKEY>::makeReply(std::string const& channel)
{
	return channel + " :Cannot join channel (+k)";
}

std::string ReplyFactory<ERR_BADCHANMASK>::makeReply(std::string const& channel)
{
	return channel + " :Bad Channel Mask";
}

std::string ReplyFactory<ERR_NOCHANMODES>::makeReply(std::string const& channel)
{
	return channel + " :Channel doesn't support modes";
}

std::string ReplyFactory<ERR_BANLISTFULL>::makeReply(std::string const& channel, std::string const& c)
{
	return channel + c + " :Channel list is full";
}

std::string ReplyFactory<ERR_NOPRIVILEGES>::makeReply()
{
	return ":Permission Denied- You're not an IRC operator";
}

std::string ReplyFactory<ERR_CHANOPRIVSNEEDED>::makeReply(std::string const& channel)
{
	return channel + " :You're not channel operator";
}
