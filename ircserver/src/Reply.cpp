/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Reply.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 18:04:40 by bbrassar          #+#    #+#             */
/*   Updated: 2022/12/17 07:03:10 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Reply.hpp"
#include "Client.hpp"
#include "config.h"

std::string const ReplyFactory<RPL_WELCOME>::NAME = "RPL_WELCOME";

std::string ReplyFactory<RPL_WELCOME>::makeReply(std::string const& nickname, std::string const& username, std::string const& hostname)
{
	return ":Welcome to the Internet Relay Network " + nickname + '!' + username + '@' + hostname;
}

std::string const ReplyFactory<RPL_YOURHOST>::NAME = "RPL_YOURHOST";

std::string ReplyFactory<RPL_YOURHOST>::makeReply()
{
	return ":Your host is " SERVER_NAME ", running version " VERSION;
};

std::string const ReplyFactory<RPL_CREATED>::NAME = "RPL_CREATED";

std::string ReplyFactory<RPL_CREATED>::makeReply(std::string const& startDate)
{
	return ":This server was created " + startDate;
};

std::string const ReplyFactory<RPL_MYINFO>::NAME = "RPL_MYINFO";

std::string ReplyFactory<RPL_MYINFO>::makeReply(std::string const& serverName)
{
	return ":" + serverName + " " VERSION " io iklo";
};

std::string const ReplyFactory<RPL_UMODEIS>::NAME = "RPL_UMODEIS";

std::string ReplyFactory<RPL_UMODEIS>::makeReply(std::string const& userModes)
{
	return userModes;
}

std::string const ReplyFactory<RPL_LIST>::NAME = "RPL_LIST";

std::string ReplyFactory<RPL_LIST>::makeReply(std::string const& channel, std::string const& visibleClients, std::string const& topic)
{
	return channel + " " + visibleClients + " :" + topic;
}

std::string const ReplyFactory<RPL_LISTEND>::NAME = "RPL_LISTEND";

std::string ReplyFactory<RPL_LISTEND>::makeReply()
{
	return ":End of /LIST";
}

std::string const ReplyFactory<RPL_CHANNELMODEIS>::NAME = "RPL_CHANNELMODEIS";

std::string ReplyFactory<RPL_CHANNELMODEIS>::makeReply(std::string const& channel, std::string const& mode) // removed params
{
	return channel + " " + mode + " ";
}

std::string const ReplyFactory<RPL_UNIQOPIS>::NAME = "RPL_UNIQOPIS";

std::string ReplyFactory<RPL_UNIQOPIS>::makeReply(std::string const& channel, std::string const& nickname)
{
	return channel + " " + nickname;
}

std::string const ReplyFactory<RPL_NOTOPIC>::NAME = "RPL_NOTOPIC";

std::string ReplyFactory<RPL_NOTOPIC>::makeReply(std::string const& channel)
{
	return channel + " :No topic is set";
}

std::string const ReplyFactory<RPL_TOPIC>::NAME = "RPL_TOPIC";

std::string ReplyFactory<RPL_TOPIC>::makeReply(std::string const& channel, std::string const& topic)
{
	return channel + " :" + topic;
}

std::string const ReplyFactory<RPL_INVITING>::NAME = "RPL_INVITING";

std::string ReplyFactory<RPL_INVITING>::makeReply(std::string const& nick, std::string const& channel)
{
	return nick + " " + channel;
}

std::string const ReplyFactory<RPL_NAMREPLY>::NAME = "RPL_NAMREPLY";

std::string ReplyFactory<RPL_NAMREPLY>::makeReply(std::string const& symbol, std::string const& channel, std::string const& clientList)
{
	return symbol + " " + channel + " :" + clientList;
}

std::string const ReplyFactory<RPL_ENDOFNAMES>::NAME = "RPL_ENDOFNAMES";

std::string ReplyFactory<RPL_ENDOFNAMES>::makeReply(std::string const& channel)
{
	return channel + " :End of /NAMES list";
}

std::string const ReplyFactory<RPL_MOTD>::NAME = "RPL_MOTD";

std::string ReplyFactory<RPL_MOTD>::makeReply(std::string const& text)
{
	return ":- " + text;
}

std::string const ReplyFactory<RPL_MOTDSTART>::NAME = "RPL_MOTDSTART";

std::string ReplyFactory<RPL_MOTDSTART>::makeReply(std::string const& serverName)
{
	return ":- " + serverName + " Message of the day -";
}

std::string const ReplyFactory<RPL_ENDOFMOTD>::NAME = "RPL_ENDOFMOTD";

std::string ReplyFactory<RPL_ENDOFMOTD>::makeReply()
{
	return ":End of MOTD command";
}

std::string const ReplyFactory<RPL_YOUREOPER>::NAME = "RPL_YOUREOPER";

std::string ReplyFactory<RPL_YOUREOPER>::makeReply()
{
	return ":You are now an IRC operator";
}

std::string const ReplyFactory<ERR_NOSUCHNICK>::NAME = "ERR_NOSUCHNICK";

std::string ReplyFactory<ERR_NOSUCHNICK>::makeReply(std::string const& nickname)
{
	return nickname + " :No such nick/channel";
}

std::string const ReplyFactory<ERR_NOSUCHCHANNEL>::NAME = "ERR_NOSUCHCHANNEL";

std::string ReplyFactory<ERR_NOSUCHCHANNEL>::makeReply(std::string const& channel)
{
	return channel + " :No such channel";
}

std::string const ReplyFactory<ERR_CANNOTSENDTOCHAN>::NAME = "ERR_CANNOTSENDTOCHAN";

std::string ReplyFactory<ERR_CANNOTSENDTOCHAN>::makeReply(std::string const& channel)
{
	return channel + " :Cannot send to channel";
}

std::string const ReplyFactory<ERR_TOOMANYCHANNELS>::NAME = "ERR_TOOMANYCHANNELS";

std::string ReplyFactory<ERR_TOOMANYCHANNELS>::makeReply(std::string const& channel)
{
	return channel + " :You have joined too many channels";
}

std::string const ReplyFactory<ERR_TOOMANYTARGETS>::NAME = "ERR_TOOMANYTARGETS";

std::string ReplyFactory<ERR_TOOMANYTARGETS>::makeReply(std::string const& target, std::string const& errorCode, std::string const& abortMessage)
{
	return target + " :" + errorCode + " recipients. " + abortMessage;
}

std::string const ReplyFactory<ERR_NOORIGIN>::NAME = "ERR_NOORIGIN";

std::string ReplyFactory<ERR_NOORIGIN>::makeReply()
{
	return ":No origin specified";
}

std::string const ReplyFactory<ERR_NOTEXTTOSEND>::NAME = "ERR_NOTEXTTOSEND";

std::string ReplyFactory<ERR_NOTEXTTOSEND>::makeReply()
{
	return ":No text to send";
}

std::string const ReplyFactory<ERR_NOTOPLEVEL>::NAME = "ERR_NOTOPLEVEL";

std::string ReplyFactory<ERR_NOTOPLEVEL>::makeReply()
{
	return ":No toplevel domain specified";
}

std::string const ReplyFactory<ERR_WILDTOPLEVEL>::NAME = "ERR_WILDTOPLEVEL";

std::string ReplyFactory<ERR_WILDTOPLEVEL>::makeReply(std::string const& mask)
{
	return mask + " :Wildcard in toplevel domain";
}

std::string const ReplyFactory<ERR_BADMASK>::NAME = "ERR_BADMASK";

std::string ReplyFactory<ERR_BADMASK>::makeReply(std::string const& mask)
{
	return mask + " :Bad Server/host mask";
}

std::string const ReplyFactory<ERR_UNKNOWNCOMMAND>::NAME = "ERR_UNKNOWNCOMMAND";

std::string ReplyFactory<ERR_UNKNOWNCOMMAND>::makeReply(std::string const& command)
{
	return command + " :Unknown command";
}

std::string const ReplyFactory<ERR_NOMOTD>::NAME = "ERR_NOMOTD";

std::string ReplyFactory<ERR_NOMOTD>::makeReply()
{
	return ":MOTD File is missing";
}

std::string const ReplyFactory<ERR_FILEERROR>::NAME = "ERR_FILEERROR";

std::string ReplyFactory<ERR_FILEERROR>::makeReply(std::string const& operation, std::string const& name)
{
	return ":File error doing " + operation + " on " + name;
}

std::string const ReplyFactory<ERR_NONICKNAMEGIVEN>::NAME = "ERR_NONICKNAMEGIVEN";

std::string ReplyFactory<ERR_NONICKNAMEGIVEN>::makeReply()
{
	return ":No nickname given";
}

std::string const ReplyFactory<ERR_ERRONEUSNICKNAME>::NAME = "ERR_ERRONEUSNICKNAME";

std::string ReplyFactory<ERR_ERRONEUSNICKNAME>::makeReply(std::string const& nickname)
{
	return nickname + " :Erroneous nickname";
}

std::string const ReplyFactory<ERR_NICKNAMEINUSE>::NAME = "ERR_NICKNAMEINUSE";

std::string ReplyFactory<ERR_NICKNAMEINUSE>::makeReply(std::string const& nickname)
{
	return nickname + " " + nickname + " :Nickname is already in use";
}

std::string const ReplyFactory<ERR_UNAVAILRESOURCE>::NAME = "ERR_UNAVAILRESOURCE";

std::string ReplyFactory<ERR_UNAVAILRESOURCE>::makeReply(std::string const& resource)
{
	return resource + " :Nick/channel is temporarily unavailable";
}

std::string const ReplyFactory<ERR_USERNOTINCHANNEL>::NAME = "ERR_USERNOTINCHANNEL";

std::string ReplyFactory<ERR_USERNOTINCHANNEL>::makeReply(std::string const& nickname, std::string const& channel)
{
	return nickname + " " + channel + " :They aren't on that channel";
}

std::string const ReplyFactory<ERR_NOTONCHANNEL>::NAME = "ERR_NOTONCHANNEL";

std::string ReplyFactory<ERR_NOTONCHANNEL>::makeReply(std::string const& channel)
{
	return channel + " :You're not on that channel";
}

std::string const ReplyFactory<ERR_USERONCHANNEL>::NAME = "ERR_USERONCHANNEL";

std::string ReplyFactory<ERR_USERONCHANNEL>::makeReply(std::string const& user, std::string const& channel)
{
	return user + " " + channel + " :is already on channel";
}

std::string const ReplyFactory<ERR_NOLOGIN>::NAME = "ERR_NOLOGIN";

std::string ReplyFactory<ERR_NOLOGIN>::makeReply(std::string const& user)
{
	return user + " :User not logged in";
}

std::string const ReplyFactory<ERR_SUMMONDISABLED>::NAME = "ERR_SUMMONDISABLED";

std::string ReplyFactory<ERR_SUMMONDISABLED>::makeReply()
{
	return ":SUMMON has been disabled";
}

std::string const ReplyFactory<ERR_USERSDISABLED>::NAME = "ERR_USERSDISABLED";

std::string ReplyFactory<ERR_USERSDISABLED>::makeReply()
{
	return ":USERS has been disabled";
}

std::string const ReplyFactory<ERR_NEEDMOREPARAMS>::NAME = "ERR_NEEDMOREPARAMS";

std::string ReplyFactory<ERR_NEEDMOREPARAMS>::makeReply(std::string const& command)
{
	return command + " :Not enough parameters";
}

std::string const ReplyFactory<ERR_ALREADYREGISTRED>::NAME = "ERR_ALREADYREGISTRED";

std::string ReplyFactory<ERR_ALREADYREGISTRED>::makeReply()
{
	return ":Unauthorized command (already registered)";
}

std::string const ReplyFactory<ERR_NOPERMFORHOST>::NAME = "ERR_NOPERMFORHOST";

std::string ReplyFactory<ERR_NOPERMFORHOST>::makeReply()
{
	return ":Your host isn't among the privileged";
}

std::string const ReplyFactory<ERR_PASSWDMISMATCH>::NAME = "ERR_PASSWDMISMATCH";

std::string ReplyFactory<ERR_PASSWDMISMATCH>::makeReply()
{
	return ":Password incorrect";
}

std::string const ReplyFactory<ERR_YOUREBANNEDCREEP>::NAME = "ERR_YOUREBANNEDCREEP";

std::string ReplyFactory<ERR_YOUREBANNEDCREEP>::makeReply()
{
	return ":You are banned from this server";
}

std::string const ReplyFactory<ERR_KEYSET>::NAME = "ERR_KEYSET";

std::string ReplyFactory<ERR_KEYSET>::makeReply(std::string const& channel)
{
	return channel + " :Channel key already set";
}

std::string const ReplyFactory<ERR_CHANNELISFULL>::NAME = "ERR_CHANNELISFULL";

std::string ReplyFactory<ERR_CHANNELISFULL>::makeReply(std::string const& channel)
{
	return channel + " :Cannot join channel (+l)";
}

std::string const ReplyFactory<ERR_UNKNOWNMODE>::NAME = "ERR_UNKNOWNMODE";

std::string ReplyFactory<ERR_UNKNOWNMODE>::makeReply(std::string const& c, std::string const& channel)
{
	return c + " :is unknown mode char to me for " + channel;
}

std::string const ReplyFactory<ERR_INVITEONLYCHAN>::NAME = "ERR_INVITEONLYCHAN";

std::string ReplyFactory<ERR_INVITEONLYCHAN>::makeReply(std::string const& channel)
{
	return channel + " :Cannot join channel (+i)";
}

std::string const ReplyFactory<ERR_BANNEDFROMCHAN>::NAME = "ERR_BANNEDFROMCHAN";

std::string ReplyFactory<ERR_BANNEDFROMCHAN>::makeReply(std::string const& channel)
{
	return channel + " :Cannot join channel (+b)";
}

std::string const ReplyFactory<ERR_BADCHANNELKEY>::NAME = "ERR_BADCHANNELKEY";

std::string ReplyFactory<ERR_BADCHANNELKEY>::makeReply(std::string const& channel)
{
	return channel + " :Cannot join channel (+k)";
}

std::string const ReplyFactory<ERR_BADCHANMASK>::NAME = "ERR_BADCHANMASK";

std::string ReplyFactory<ERR_BADCHANMASK>::makeReply(std::string const& channel)
{
	return channel + " :Bad Channel Mask";
}

std::string const ReplyFactory<ERR_NOCHANMODES>::NAME = "ERR_NOCHANMODES";

std::string ReplyFactory<ERR_NOCHANMODES>::makeReply(std::string const& channel)
{
	return channel + " :Channel doesn't support modes";
}

std::string const ReplyFactory<ERR_BANLISTFULL>::NAME = "ERR_BANLISTFULL";

std::string ReplyFactory<ERR_BANLISTFULL>::makeReply(std::string const& channel, std::string const& c)
{
	return channel + c + " :Channel list is full";
}

std::string const ReplyFactory<ERR_NOPRIVILEGES>::NAME = "ERR_NOPRIVILEGES";

std::string ReplyFactory<ERR_NOPRIVILEGES>::makeReply()
{
	return ":Permission Denied- You're not an IRC operator";
}

std::string const ReplyFactory<ERR_CHANOPRIVSNEEDED>::NAME = "ERR_CHANOPRIVSNEEDED";

std::string ReplyFactory<ERR_CHANOPRIVSNEEDED>::makeReply(std::string const& channel)
{
	return channel + " :You're not channel operator";
}

std::string const ReplyFactory<ERR_UMODEUNKNOWNFLAG>::NAME = "ERR_UMODEUNKNOWNFLAG";

std::string ReplyFactory<ERR_UMODEUNKNOWNFLAG>::makeReply()
{
	return ":Unknown MODE flag";
}

std::string const ReplyFactory<ERR_USERSDONTMATCH>::NAME = "ERR_USERSDONTMATCH";

std::string ReplyFactory<ERR_USERSDONTMATCH>::makeReply()
{
	return ":Cant change mode for other users";
}
