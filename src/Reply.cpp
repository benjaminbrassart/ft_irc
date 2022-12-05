/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Reply.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 18:04:40 by bbrassar          #+#    #+#             */
/*   Updated: 2022/12/05 13:08:19 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Reply.hpp"
#include "Client.hpp"
#include "config.h"

std::string const ReplyFactory<RPL_WELCOME>::NAME = "RPL_WELCOME";

std::string ReplyFactory<RPL_WELCOME>::makeReply(Client& client, std::string const& nickname, std::string const& username, std::string const& hostname)
{
	return client.nickname + " :Welcome to the Internet Relay Network " + nickname + '!' + username + '@' + hostname;
}

std::string const ReplyFactory<RPL_YOURHOST>::NAME = "RPL_YOURHOST";

std::string ReplyFactory<RPL_YOURHOST>::makeReply(Client& client)
{
	return client.nickname + " :Your host is " SERVER_NAME ", running version " VERSION;
};

std::string const ReplyFactory<RPL_CREATED>::NAME = "RPL_CREATED";

std::string ReplyFactory<RPL_CREATED>::makeReply(Client& client, std::string const& startDate)
{
	return client.nickname + " :This server was created " + startDate;
};

std::string const ReplyFactory<RPL_MYINFO>::NAME = "RPL_MYINFO";

std::string ReplyFactory<RPL_MYINFO>::makeReply(Client& client, std::string const& serverName)
{
	return client.nickname + " :" + serverName + " " VERSION " o O"; // TODO add channel modes
};

std::string const ReplyFactory<RPL_LIST>::NAME = "RPL_LIST";

std::string ReplyFactory<RPL_LIST>::makeReply(Client& client, std::string const& channel, std::string const& visibleClients, std::string const& topic)
{
	(void)client;
	return channel + " " + visibleClients + " :" + topic;
}

std::string const ReplyFactory<RPL_LISTEND>::NAME = "RPL_LISTEND";

std::string ReplyFactory<RPL_LISTEND>::makeReply(Client& client)
{
	(void)client;
	return ":End of LIST";
}

std::string const ReplyFactory<RPL_CHANNELMODEIS>::NAME = "RPL_CHANNELMODEIS";

std::string ReplyFactory<RPL_CHANNELMODEIS>::makeReply(Client& client, std::string const& channel, std::string const& mode, std::string const& params)
{
	(void)client;
	return channel + " " + mode + " " + params;
}

std::string const ReplyFactory<RPL_UNIQOPIS>::NAME = "RPL_UNIQOPIS";

std::string ReplyFactory<RPL_UNIQOPIS>::makeReply(Client& client, std::string const& channel, std::string const& nickname)
{
	(void)client;
	return channel + " " + nickname;
}

std::string const ReplyFactory<RPL_NOTOPIC>::NAME = "RPL_NOTOPIC";

std::string ReplyFactory<RPL_NOTOPIC>::makeReply(Client& client, std::string const& channel)
{
	(void)client;
	return channel + " :No topic is set";
}

std::string const ReplyFactory<RPL_TOPIC>::NAME = "RPL_TOPIC";

std::string ReplyFactory<RPL_TOPIC>::makeReply(Client& client, std::string const& channel, std::string const& topic)
{
	(void)client;
	return channel + " :" + topic;
}

std::string const ReplyFactory<RPL_NAMREPLY>::NAME = "RPL_NAMREPLY";

std::string ReplyFactory<RPL_NAMREPLY>::makeReply(Client& client, std::string const& symbol, std::string const& channel, std::string const& clientList)
{
	(void)client;
	return symbol + " " + channel + " :" + clientList;
}

std::string const ReplyFactory<RPL_ENDOFNAMES>::NAME = "RPL_ENDOFNAMES";

std::string ReplyFactory<RPL_ENDOFNAMES>::makeReply(Client& client, std::string const& channel)
{
	(void)client;
	return channel + " :End of /NAMES list";
}

std::string const ReplyFactory<RPL_MOTD>::NAME = "RPL_MOTD";

std::string ReplyFactory<RPL_MOTD>::makeReply(Client& client, std::string const& text)
{
	(void)client;
	return ":- " + text;
}

std::string const ReplyFactory<RPL_MOTDSTART>::NAME = "RPL_MOTDSTART";

std::string ReplyFactory<RPL_MOTDSTART>::makeReply(Client& client, std::string const& serverName)
{
	(void)client;
	return ":- " + serverName + " Message of the day -";
}

std::string const ReplyFactory<RPL_ENDOFMOTD>::NAME = "RPL_ENDOFMOTD";

std::string ReplyFactory<RPL_ENDOFMOTD>::makeReply(Client& client)
{
	(void)client;
	return ":End of MOTD command";
}

std::string const ReplyFactory<RPL_YOUREOPER>::NAME = "RPL_YOUREOPER";

std::string ReplyFactory<RPL_YOUREOPER>::makeReply(Client& client)
{
	(void)client;
	return ":You are now an IRC operator";
}

std::string const ReplyFactory<ERR_NOSUCHNICK>::NAME = "ERR_NOSUCHNICK";

std::string ReplyFactory<ERR_NOSUCHNICK>::makeReply(Client& client, std::string const& nickname)
{
	(void)client;
	return nickname + " :No such nick/channel";
}

std::string const ReplyFactory<ERR_NOSUCHCHANNEL>::NAME = "ERR_NOSUCHCHANNEL";

std::string ReplyFactory<ERR_NOSUCHCHANNEL>::makeReply(Client& client, std::string const& channel)
{
	(void)client;
	return channel + " :No such channel";
}

std::string const ReplyFactory<ERR_CANNOTSENDTOCHAN>::NAME = "ERR_CANNOTSENDTOCHAN";

std::string ReplyFactory<ERR_CANNOTSENDTOCHAN>::makeReply(Client& client, std::string const& channel)
{
	(void)client;
	return channel + " :Cannot send to channel";
}

std::string const ReplyFactory<ERR_TOOMANYCHANNELS>::NAME = "ERR_TOOMANYCHANNELS";

std::string ReplyFactory<ERR_TOOMANYCHANNELS>::makeReply(Client& client, std::string const& channel)
{
	(void)client;
	return channel + " :You have joined too many channels";
}

std::string const ReplyFactory<ERR_TOOMANYTARGETS>::NAME = "ERR_TOOMANYTARGETS";

std::string ReplyFactory<ERR_TOOMANYTARGETS>::makeReply(Client& client, std::string const& target, std::string const& errorCode, std::string const& abortMessage)
{
	(void)client;
	return target + " :" + errorCode + " recipients. " + abortMessage;
}

std::string const ReplyFactory<ERR_NOORIGIN>::NAME = "ERR_NOORIGIN";

std::string ReplyFactory<ERR_NOORIGIN>::makeReply(Client& client)
{
	(void)client;
	return ":No origin specified";
}

std::string const ReplyFactory<ERR_NOTEXTTOSEND>::NAME = "ERR_NOTEXTTOSEND";

std::string ReplyFactory<ERR_NOTEXTTOSEND>::makeReply(Client& client)
{
	(void)client;
	return ":No text to send";
}

std::string const ReplyFactory<ERR_NOTOPLEVEL>::NAME = "ERR_NOTOPLEVEL";

std::string ReplyFactory<ERR_NOTOPLEVEL>::makeReply(Client& client)
{
	(void)client;
	return ":No toplevel domain specified";
}

std::string const ReplyFactory<ERR_WILDTOPLEVEL>::NAME = "ERR_WILDTOPLEVEL";

std::string ReplyFactory<ERR_WILDTOPLEVEL>::makeReply(Client& client, std::string const& mask)
{
	(void)client;
	return mask + " :Wildcard in toplevel domain";
}

std::string const ReplyFactory<ERR_BADMASK>::NAME = "ERR_BADMASK";

std::string ReplyFactory<ERR_BADMASK>::makeReply(Client& client, std::string const& mask)
{
	(void)client;
	return mask + " :Bad Server/host mask";
}

std::string const ReplyFactory<ERR_UNKNOWNCOMMAND>::NAME = "ERR_UNKNOWNCOMMAND";

std::string ReplyFactory<ERR_UNKNOWNCOMMAND>::makeReply(Client& client, std::string const& command)
{
	(void)client;
	return command + " :Unknown command";
}

std::string const ReplyFactory<ERR_NOMOTD>::NAME = "ERR_NOMOTD";

std::string ReplyFactory<ERR_NOMOTD>::makeReply(Client& client)
{
	(void)client;
	return ":MOTD File is missing";
}

std::string const ReplyFactory<ERR_FILEERROR>::NAME = "ERR_FILEERROR";

std::string ReplyFactory<ERR_FILEERROR>::makeReply(Client& client, std::string const& operation, std::string const& name)
{
	(void)client;
	return ":File error doing " + operation + " on " + name;
}

std::string const ReplyFactory<ERR_NONICKNAMEGIVEN>::NAME = "ERR_NONICKNAMEGIVEN";

std::string ReplyFactory<ERR_NONICKNAMEGIVEN>::makeReply(Client& client)
{
	(void)client;
	return ":No nickname given";
}

std::string const ReplyFactory<ERR_ERRONEUSNICKNAME>::NAME = "ERR_ERRONEUSNICKNAME";

std::string ReplyFactory<ERR_ERRONEUSNICKNAME>::makeReply(Client& client, std::string const& nickname)
{
	(void)client;
	return nickname + " :Erroneous nickname";
}

std::string const ReplyFactory<ERR_NICKNAMEINUSE>::NAME = "ERR_NICKNAMEINUSE";

std::string ReplyFactory<ERR_NICKNAMEINUSE>::makeReply(Client& client, std::string const& nickname)
{
	(void)client;
	return nickname + " " + nickname + " :Nickname is already in use";
}

std::string const ReplyFactory<ERR_UNAVAILRESOURCE>::NAME = "ERR_UNAVAILRESOURCE";

std::string ReplyFactory<ERR_UNAVAILRESOURCE>::makeReply(Client& client, std::string const& resource)
{
	(void)client;
	return resource + " :Nick/channel is temporarily unavailable";
}

std::string const ReplyFactory<ERR_USERNOTINCHANNEL>::NAME = "ERR_USERNOTINCHANNEL";

std::string ReplyFactory<ERR_USERNOTINCHANNEL>::makeReply(Client& client, std::string const& nickname, std::string const& channel)
{
	(void)client;
	return nickname + " " + channel + " :They aren't on that channel";
}

std::string const ReplyFactory<ERR_NOTONCHANNEL>::NAME = "ERR_NOTONCHANNEL";

std::string ReplyFactory<ERR_NOTONCHANNEL>::makeReply(Client& client, std::string const& channel)
{
	(void)client;
	return channel + " :You're not on that channel";
}

std::string const ReplyFactory<ERR_USERONCHANNEL>::NAME = "ERR_USERONCHANNEL";

std::string ReplyFactory<ERR_USERONCHANNEL>::makeReply(Client& client, std::string const& user, std::string const& channel)
{
	(void)client;
	return user + " " + channel + " :is already on channel";
}

std::string const ReplyFactory<ERR_NOLOGIN>::NAME = "ERR_NOLOGIN";

std::string ReplyFactory<ERR_NOLOGIN>::makeReply(Client& client, std::string const& user)
{
	(void)client;
	return user + " :User not logged in";
}

std::string const ReplyFactory<ERR_SUMMONDISABLED>::NAME = "ERR_SUMMONDISABLED";

std::string ReplyFactory<ERR_SUMMONDISABLED>::makeReply(Client& client)
{
	(void)client;
	return ":SUMMON has been disabled";
}

std::string const ReplyFactory<ERR_USERSDISABLED>::NAME = "ERR_USERSDISABLED";

std::string ReplyFactory<ERR_USERSDISABLED>::makeReply(Client& client)
{
	(void)client;
	return ":USERS has been disabled";
}

std::string const ReplyFactory<ERR_NEEDMOREPARAMS>::NAME = "ERR_NEEDMOREPARAMS";

std::string ReplyFactory<ERR_NEEDMOREPARAMS>::makeReply(Client& client, std::string const& command)
{
	(void)client;
	return command + " :Not enough parameters";
}

std::string const ReplyFactory<ERR_ALREADYREGISTRED>::NAME = "ERR_ALREADYREGISTRED";

std::string ReplyFactory<ERR_ALREADYREGISTRED>::makeReply(Client& client)
{
	(void)client;
	return client.nickname + " :Unauthorized command (already registered)";
}

std::string const ReplyFactory<ERR_NOPERMFORHOST>::NAME = "ERR_NOPERMFORHOST";

std::string ReplyFactory<ERR_NOPERMFORHOST>::makeReply(Client& client)
{
	(void)client;
	return ":Your host isn't among the privileged";
}

std::string const ReplyFactory<ERR_PASSWDMISMATCH>::NAME = "ERR_PASSWDMISMATCH";

std::string ReplyFactory<ERR_PASSWDMISMATCH>::makeReply(Client& client)
{
	return client.nickname + " :Password incorrect";
}

std::string const ReplyFactory<ERR_YOUREBANNEDCREEP>::NAME = "ERR_YOUREBANNEDCREEP";

std::string ReplyFactory<ERR_YOUREBANNEDCREEP>::makeReply(Client& client)
{
	(void)client;
	return ":You are banned from this server";
}

std::string const ReplyFactory<ERR_YOUWILLBEBANNED>::NAME = "ERR_YOUWILLBEBANNED";

std::string ReplyFactory<ERR_YOUWILLBEBANNED>::makeReply(Client& client)
{
	(void)client;
	return ""; // TODO
}


std::string const ReplyFactory<ERR_KEYSET>::NAME = "ERR_KEYSET";

std::string ReplyFactory<ERR_KEYSET>::makeReply(Client& client, std::string const& channel)
{
	(void)client;
	return channel + " :Channel key already set";
}

std::string const ReplyFactory<ERR_CHANNELISFULL>::NAME = "ERR_CHANNELISFULL";

std::string ReplyFactory<ERR_CHANNELISFULL>::makeReply(Client& client, std::string const& channel)
{
	(void)client;
	return channel + " :Cannot join channel (+l)";
}

std::string const ReplyFactory<ERR_UNKNOWNMODE>::NAME = "ERR_UNKNOWNMODE";

std::string ReplyFactory<ERR_UNKNOWNMODE>::makeReply(Client& client, std::string const& c, std::string const& channel)
{
	(void)client;
	return c + " :is unknown mode char to me for " + channel;
}

std::string const ReplyFactory<ERR_INVITEONLYCHAN>::NAME = "ERR_INVITEONLYCHAN";

std::string ReplyFactory<ERR_INVITEONLYCHAN>::makeReply(Client& client, std::string const& channel)
{
	(void)client;
	return channel + " :Cannot join channel (+i)";
}

std::string const ReplyFactory<ERR_BANNEDFROMCHAN>::NAME = "ERR_BANNEDFROMCHAN";

std::string ReplyFactory<ERR_BANNEDFROMCHAN>::makeReply(Client& client, std::string const& channel)
{
	(void)client;
	return channel + " :Cannot join channel (+b)";
}

std::string const ReplyFactory<ERR_BADCHANNELKEY>::NAME = "ERR_BADCHANNELKEY";

std::string ReplyFactory<ERR_BADCHANNELKEY>::makeReply(Client& client, std::string const& channel)
{
	(void)client;
	return channel + " :Cannot join channel (+k)";
}

std::string const ReplyFactory<ERR_BADCHANMASK>::NAME = "ERR_BADCHANMASK";

std::string ReplyFactory<ERR_BADCHANMASK>::makeReply(Client& client, std::string const& channel)
{
	(void)client;
	return channel + " :Bad Channel Mask";
}

std::string const ReplyFactory<ERR_NOCHANMODES>::NAME = "ERR_NOCHANMODES";

std::string ReplyFactory<ERR_NOCHANMODES>::makeReply(Client& client, std::string const& channel)
{
	(void)client;
	return channel + " :Channel doesn't support modes";
}

std::string const ReplyFactory<ERR_BANLISTFULL>::NAME = "ERR_BANLISTFULL";

std::string ReplyFactory<ERR_BANLISTFULL>::makeReply(Client& client, std::string const& channel, std::string const& c)
{
	(void)client;
	return channel + c + " :Channel list is full";
}

std::string const ReplyFactory<ERR_NOPRIVILEGES>::NAME = "ERR_NOPRIVILEGES";

std::string ReplyFactory<ERR_NOPRIVILEGES>::makeReply(Client& client)
{
	(void)client;
	return ":Permission Denied- You're not an IRC operator";
}

std::string const ReplyFactory<ERR_CHANOPRIVSNEEDED>::NAME = "ERR_CHANOPRIVSNEEDED";

std::string ReplyFactory<ERR_CHANOPRIVSNEEDED>::makeReply(Client& client, std::string const& channel)
{
	(void)client;
	return channel + " :You're not channel operator";
}
