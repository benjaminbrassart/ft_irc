/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Reply.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 01:45:10 by bbrassar          #+#    #+#             */
/*   Updated: 2022/12/16 21:51:31 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REPLY_HPP
# define REPLY_HPP

# include <string>

enum Reply
{
	RPL_WELCOME = 1,
	RPL_YOURHOST = 2,
	RPL_CREATED = 3,
	RPL_MYINFO = 4,
	RPL_UMODEIS = 221,
	RPL_LIST = 322,
	RPL_LISTEND = 323,
	RPL_CHANNELMODEIS = 324,
	RPL_UNIQOPIS = 325,
	RPL_NOTOPIC = 331,
	RPL_TOPIC = 332,
	RPL_INVITING = 341,
	RPL_NAMREPLY = 353,
	RPL_ENDOFNAMES = 366,
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
	ERR_ERRONEUSNICKNAME = 432,
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
	ERR_UMODEUNKNOWNFLAG = 501,
	ERR_USERSDONTMATCH = 502,

}; // enum Reply

class Client;

template< Reply code >
struct ReplyFactory
{
};

template<>
struct ReplyFactory<RPL_WELCOME>
{
	static std::string const NAME;
	static std::string makeReply(std::string const& nickname, std::string const& user, std::string const& host);
};

template<>
struct ReplyFactory<RPL_YOURHOST>
{
	static std::string const NAME;
	static std::string makeReply();
};

template<>
struct ReplyFactory<RPL_CREATED>
{
	static std::string const NAME;
	static std::string makeReply(std::string const& startDate);
};

template<>
struct ReplyFactory<RPL_MYINFO>
{
	static std::string const NAME;
	static std::string makeReply(std::string const& serverName);
};

template<>
struct ReplyFactory<RPL_UMODEIS>
{
	static std::string const NAME;
	static std::string makeReply(std::string const& user, std::string const& userModes);
};

template<>
struct ReplyFactory<RPL_LIST>
{
	static std::string const NAME;
	static std::string makeReply(std::string const& channel, std::string const& visibleClients, std::string const& topic);
};

template<>
struct ReplyFactory<RPL_LISTEND>
{
	static std::string const NAME;
	static std::string makeReply();
};

template<>
struct ReplyFactory<RPL_CHANNELMODEIS>
{
	static std::string const NAME;
	static std::string makeReply(std::string const& channel, std::string const& mode); // removed params
};

template<>
struct ReplyFactory<RPL_UNIQOPIS>
{
	static std::string const NAME;
	static std::string makeReply(std::string const& channel, std::string const& nickname);
};

template<>
struct ReplyFactory<RPL_NOTOPIC>
{
	static std::string const NAME;
	static std::string makeReply(std::string const& channel);
};

template<>
struct ReplyFactory<RPL_TOPIC>
{
	static std::string const NAME;
	static std::string makeReply(std::string const& channel, std::string const& topic);
};

template<>
struct ReplyFactory<RPL_INVITING>
{
	static std::string const NAME;
	static std::string makeReply(std::string const& nick, std::string const& channel);
};

template<>
struct ReplyFactory<RPL_NAMREPLY>
{
	static std::string const NAME;
	static std::string makeReply(std::string const& symbol, std::string const& channel, std::string const& clientList);
};

template<>
struct ReplyFactory<RPL_ENDOFNAMES>
{
	static std::string const NAME;
	static std::string makeReply(std::string const& channel);
};

template<>
struct ReplyFactory<RPL_MOTD>
{
	static std::string const NAME;
	static std::string makeReply(std::string const& text);
};

template<>
struct ReplyFactory<RPL_MOTDSTART>
{
	static std::string const NAME;
	static std::string makeReply(std::string const& serverName);
};

template<>
struct ReplyFactory<RPL_ENDOFMOTD>
{
	static std::string const NAME;
	static std::string makeReply();
};
template<>
struct ReplyFactory<RPL_YOUREOPER>
{
	static std::string const NAME;
	static std::string makeReply();
};

template<>
struct ReplyFactory<ERR_NOSUCHNICK>
{
	static std::string const NAME;
	static std::string makeReply(std::string const& nickname);
};

template<>
struct ReplyFactory<ERR_NOSUCHCHANNEL>
{
	static std::string const NAME;
	static std::string makeReply(std::string const& channel);
};

template<>
struct ReplyFactory<ERR_CANNOTSENDTOCHAN>
{
	static std::string const NAME;
	static std::string makeReply(std::string const& channel);
};

template<>
struct ReplyFactory<ERR_TOOMANYCHANNELS>
{
	static std::string const NAME;
	static std::string makeReply(std::string const& channel);
};

template<>
struct ReplyFactory<ERR_TOOMANYTARGETS>
{
	static std::string const NAME;
	static std::string makeReply(std::string const& target, std::string const& errorCode, std::string const& abortMessage);
};

template<>
struct ReplyFactory<ERR_NOORIGIN>
{
	static std::string const NAME;
	static std::string makeReply();
};

template<>
struct ReplyFactory<ERR_NOTEXTTOSEND>
{
	static std::string const NAME;
	static std::string makeReply();
};

template<>
struct ReplyFactory<ERR_NOTOPLEVEL>
{
	static std::string const NAME;
	static std::string makeReply();
};

template<>
struct ReplyFactory<ERR_WILDTOPLEVEL>
{
	static std::string const NAME;
	static std::string makeReply(std::string const& mask);
};

template<>
struct ReplyFactory<ERR_BADMASK>
{
	static std::string const NAME;
	static std::string makeReply(std::string const& mask);
};

template<>
struct ReplyFactory<ERR_UNKNOWNCOMMAND>
{
	static std::string const NAME;
	static std::string makeReply(std::string const& command);
};

template<>
struct ReplyFactory<ERR_NOMOTD>
{
	static std::string const NAME;
	static std::string makeReply();
};

template<>
struct ReplyFactory<ERR_FILEERROR>
{
	static std::string const NAME;
	static std::string makeReply(std::string const& operation, std::string const& name);
};

template<>
struct ReplyFactory<ERR_NONICKNAMEGIVEN>
{
	static std::string const NAME;
	static std::string makeReply();
};

template<>
struct ReplyFactory<ERR_ERRONEUSNICKNAME>
{
	static std::string const NAME;
	static std::string makeReply(std::string const& nickname);
};

template<>
struct ReplyFactory<ERR_NICKNAMEINUSE>
{
	static std::string const NAME;
	static std::string makeReply(std::string const& nickname);
};

template<>
struct ReplyFactory<ERR_UNAVAILRESOURCE>
{
	static std::string const NAME;
	static std::string makeReply(std::string const& resource);
};

template<>
struct ReplyFactory<ERR_USERNOTINCHANNEL>
{
	static std::string const NAME;
	static std::string makeReply(std::string const& nickname, std::string const& channel);
};

template<>
struct ReplyFactory<ERR_NOTONCHANNEL>
{
	static std::string const NAME;
	static std::string makeReply(std::string const& channel);
};

template<>
struct ReplyFactory<ERR_USERONCHANNEL>
{
	static std::string const NAME;
	static std::string makeReply(std::string const& user, std::string const& channel);
};

template<>
struct ReplyFactory<ERR_NOLOGIN>
{
	static std::string const NAME;
	static std::string makeReply(std::string const& user);
};

template<>
struct ReplyFactory<ERR_SUMMONDISABLED>
{
	static std::string const NAME;
	static std::string makeReply();
};

template<>
struct ReplyFactory<ERR_USERSDISABLED>
{
	static std::string const NAME;
	static std::string makeReply();
};

template<>
struct ReplyFactory<ERR_NEEDMOREPARAMS>
{
	static std::string const NAME;
	static std::string makeReply(std::string const& command);
};

template<>
struct ReplyFactory<ERR_ALREADYREGISTRED>
{
	static std::string const NAME;
	static std::string makeReply();
};

template<>
struct ReplyFactory<ERR_NOPERMFORHOST>
{
	static std::string const NAME;
	static std::string makeReply();
};

template<>
struct ReplyFactory<ERR_PASSWDMISMATCH>
{
	static std::string const NAME;
	static std::string makeReply();
};

template<>
struct ReplyFactory<ERR_YOUREBANNEDCREEP>
{
	static std::string const NAME;
	static std::string makeReply();
};

template<>
struct ReplyFactory<ERR_KEYSET>
{
	static std::string const NAME;
	static std::string makeReply(std::string const& channel);
};

template<>
struct ReplyFactory<ERR_CHANNELISFULL>
{
	static std::string const NAME;
	static std::string makeReply(std::string const& channel);
};

template<>
struct ReplyFactory<ERR_UNKNOWNMODE>
{
	static std::string const NAME;
	static std::string makeReply(std::string const& c, std::string const& channel);
};

template<>
struct ReplyFactory<ERR_INVITEONLYCHAN>
{
	static std::string const NAME;
	static std::string makeReply(std::string const& channel);
};

template<>
struct ReplyFactory<ERR_BANNEDFROMCHAN>
{
	static std::string const NAME;
	static std::string makeReply(std::string const& channel);
};

template<>
struct ReplyFactory<ERR_BADCHANNELKEY>
{
	static std::string const NAME;
	static std::string makeReply(std::string const& channel);
};

template<>
struct ReplyFactory<ERR_BADCHANMASK>
{
	static std::string const NAME;
	static std::string makeReply(std::string const& channel);
};

template<>
struct ReplyFactory<ERR_NOCHANMODES>
{
	static std::string const NAME;
	static std::string makeReply(std::string const& channel);
};

template<>
struct ReplyFactory<ERR_BANLISTFULL>
{
	static std::string const NAME;
	static std::string makeReply(std::string const& channel, std::string const& c);
};

template<>
struct ReplyFactory<ERR_NOPRIVILEGES>
{
	static std::string const NAME;
	static std::string makeReply();
};

template<>
struct ReplyFactory<ERR_CHANOPRIVSNEEDED>
{
	static std::string const NAME;
	static std::string makeReply(std::string const& channel);
};

template<>
struct ReplyFactory<ERR_UMODEUNKNOWNFLAG>
{
	static std::string const NAME;
	static std::string makeReply();
};

template<>
struct ReplyFactory<ERR_USERSDONTMATCH>
{
	static std::string const NAME;
	static std::string makeReply();
};

#endif // REPLY_H
