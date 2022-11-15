/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 19:28:16 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/14 20:46:28 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_HPP
# define COMMAND_HPP

# include <string>
# include <vector>

namespace irc
{
enum Reply
{
	ERR_ALREADYREGISTRED = 462,
	ERR_BADCHANMASK = 476,
	ERR_BADCHANNELKEY = 475,
	ERR_CANNOTSENDTOCHAN = 404,
	ERR_CHANNELISFULL = 471,
	ERR_ERRONEUSNICKNAME = 432,
	ERR_INVITEONLYCHAN = 473,
	ERR_NEEDMOREPARAMS = 461,
	ERR_NICKCOLLISION = 436,
	ERR_NICKNAMEINUSE = 433,
	ERR_NONICKNAMEGIVEN = 431,
	ERR_NOOPERHOST = 491,
	ERR_NORECIPIENT = 411,
	ERR_NOSUCHCHANNEL = 403,
	ERR_NOSUCHNICK = 401,
	ERR_NOTEXTTOSEND = 412,
	ERR_NOTONCHANNEL = 442,
	ERR_NOTOPLEVEL = 413,
	ERR_PASSWDMISMATCH = 464,
	ERR_TOOMANYCHANNELS = 405,
	ERR_TOOMANYTARGETS = 407,
	ERR_WILDTOPLEVEL = 414,
	RPL_AWAY = 301,
	RPL_TOPIC = 332,
	RPL_YOUREOPER = 381,
};

class command_result
{
public:
	typedef std::vector< std::string > args_container;

private:
	Reply _code;
	args_container _args;

public:
	command_result();
	command_result(int code, ...); // TODO
	command_result(int code, args_container const& args);
	command_result(command_result const& x);
	command_result& operator=(command_result const& x);
	~command_result();

public:

}; // class command_result

typedef command_result (*command_executor)(std::vector< std::string > const&);
} // namespace irc

#endif // COMMAND_HPP
