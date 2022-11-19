/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Reply.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 18:04:40 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/19 03:32:16 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Reply.hpp"

std::string ReplyFactory<RPL_WELCOME>::makeReply(std::string const& nickname, std::string const& username, std::string const& hostname)
{
	return "Welcome to the Internet Relay Network " + nickname + '!' + username + '@' + hostname;
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
