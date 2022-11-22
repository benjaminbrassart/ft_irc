/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Reply.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 01:45:10 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/21 15:57:35 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REPLY_H
# define REPLY_H

# include <string>

enum Reply
{
	RPL_WELCOME = 1,

	RPL_MOTD = 372,
	RPL_MOTDSTART = 375,
	RPL_ENDOFMOTD = 376,
	RPL_YOUREOPER = 381,

	ERR_NOSUCHNICK = 401,
	ERR_NOSUCHCHANNEL = 403,
	ERR_CANNOTSENDTOCHAN = 404,
	ERR_TOOMANYCHANNELS = 405,
	ERR_TOOMANYTARGETS = 407,
	ERR_NOORIGIN = 409,
	ERR_NORECIPIENT = 411,
	ERR_NOTEXTTOSEND = 412,
	ERR_NOTOPLEVEL = 413,
	ERR_WILDTOPLEVEL = 414,
	ERR_BADMASK = 415,
	ERR_UNKNOWNCOMMAND = 421,
	ERR_NOMOTD = 422,
	ERR_FILEERROR = 424,
	ERR_NONICKNAMEGIVEN = 431,
	ERR_ERRONEOUSNICKNAME = 432,
	ERR_NICKNAMEINUSE = 433,
	ERR_UNAVAILRESOURCE = 437,
	ERR_USERNOTINCHANNEL = 441,
	ERR_NOTONCHANNEL = 442,
	ERR_USERONCHANNEL = 443,
	ERR_NOLOGIN = 444,
	ERR_SUMMONDISABLED = 445,
	ERR_USERSDISABLED = 446,
	ERR_NOTREGISTERED = 451,
	ERR_NEEDMOREPARAMS = 461,
	ERR_ALREADYREGISTRED = 462,
	ERR_NOPERMFORHOST = 463,
	ERR_PASSWDMISMATCH = 464,
	ERR_YOUREBANNEDCREEP = 465,
	ERR_YOUWILLBEBANNED = 466,
	ERR_KEYSET = 467,
	ERR_CHANNELISFULL = 471,
	ERR_UNKNOWNMODE = 472,
	ERR_INVITEONLYCHAN = 473,
	ERR_BANNEDFROMCHAN = 474,
	ERR_BADCHANNELKEY = 475,
	ERR_BADCHANMASK = 476,
	ERR_NOCHANMODES = 477,
	ERR_BANLISTFULL = 478,
	ERR_NOPRIVILEGES = 481,
	ERR_CHANOPRIVSNEEDED = 482,
	ERR_RESTRICTED = 484,
}; // enum Reply

template< Reply code >
struct ReplyFactory
{
};

template<>
struct ReplyFactory<RPL_WELCOME>
{
	static std::string makeReply(std::string const& nickname, std::string const& user, std::string const& host);
};

template<>
struct ReplyFactory<RPL_MOTD>
{
	static std::string makeReply(std::string const& text);
};

template<>
struct ReplyFactory<RPL_MOTDSTART>
{
	static std::string makeReply(std::string const& serverName);
};

template<>
struct ReplyFactory<RPL_ENDOFMOTD>
{
	static std::string makeReply();
};
template<>
struct ReplyFactory<RPL_YOUREOPER>
{
	static std::string makeReply();
};

template<>
struct ReplyFactory<ERR_NOSUCHNICK>
{
	static std::string makeReply(std::string const& nickname);
};

template<>
struct ReplyFactory<ERR_NOSUCHCHANNEL>
{
	static std::string makeReply(std::string const& channel);
};

template<>
struct ReplyFactory<ERR_CANNOTSENDTOCHAN>
{
	static std::string makeReply(std::string const& channel);
};

template<>
struct ReplyFactory<ERR_TOOMANYCHANNELS>
{
	static std::string makeReply(std::string const& channel);
};

template<>
struct ReplyFactory<ERR_TOOMANYTARGETS>
{
	static std::string makeReply(std::string const& target, std::string const& errorCode, std::string const& abortMessage);
};

template<>
struct ReplyFactory<ERR_NOORIGIN>
{
	static std::string makeReply();
};

template<>
struct ReplyFactory<ERR_NOTEXTTOSEND>
{
	static std::string makeReply();
};

template<>
struct ReplyFactory<ERR_NOTOPLEVEL>
{
	static std::string makeReply();
};

template<>
struct ReplyFactory<ERR_WILDTOPLEVEL>
{
	static std::string makeReply(std::string const& mask);
};

template<>
struct ReplyFactory<ERR_BADMASK>
{
	static std::string makeReply(std::string const& mask);
};

template<>
struct ReplyFactory<ERR_UNKNOWNCOMMAND>
{
	static std::string makeReply(std::string const& command);
};

template<>
struct ReplyFactory<ERR_NOMOTD>
{
	static std::string makeReply();
};

template<>
struct ReplyFactory<ERR_FILEERROR>
{
	static std::string makeReply(std::string const& operation, std::string const& name);
};

template<>
struct ReplyFactory<ERR_NONICKNAMEGIVEN>
{
	static std::string makeReply();
};

template<>
struct ReplyFactory<ERR_ERRONEOUSNICKNAME>
{
	static std::string makeReply(std::string const& nickname);
};

template<>
struct ReplyFactory<ERR_NICKNAMEINUSE>
{
	static std::string makeReply(std::string const& nickname);
};

template<>
struct ReplyFactory<ERR_UNAVAILRESOURCE>
{
	static std::string makeReply(std::string const& resource);
};

template<>
struct ReplyFactory<ERR_USERNOTINCHANNEL>
{
	static std::string makeReply(std::string const& nickname, std::string const& channel);
};

template<>
struct ReplyFactory<ERR_NOTONCHANNEL>
{
	static std::string makeReply(std::string const& channel);
};

template<>
struct ReplyFactory<ERR_USERONCHANNEL>
{
	static std::string makeReply(std::string const& user, std::string const& channel);
};

template<>
struct ReplyFactory<ERR_NOLOGIN>
{
	static std::string makeReply(std::string const& user);
};

template<>
struct ReplyFactory<ERR_SUMMONDISABLED>
{
	static std::string makeReply();
};

template<>
struct ReplyFactory<ERR_USERSDISABLED>
{
	static std::string makeReply();
};

template<>
struct ReplyFactory<ERR_NEEDMOREPARAMS>
{
	static std::string makeReply(std::string const& command);
};

template<>
struct ReplyFactory<ERR_ALREADYREGISTRED>
{
	static std::string makeReply();
};

template<>
struct ReplyFactory<ERR_NOPERMFORHOST>
{
	static std::string makeReply();
};

template<>
struct ReplyFactory<ERR_PASSWDMISMATCH>
{
	static std::string makeReply();
};

template<>
struct ReplyFactory<ERR_YOUREBANNEDCREEP>
{
	static std::string makeReply();
};

template<>
struct ReplyFactory<ERR_YOUWILLBEBANNED>
{
	static std::string makeReply();
};

#endif // REPLY_H
