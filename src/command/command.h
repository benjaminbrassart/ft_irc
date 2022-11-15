/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 20:47:26 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/14 22:12:10 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# include <cstdarg>
# include <string>
# include <vector>

namespace irc
{
struct __command_arguments
{
	int _fd;
	int _len;
	char** _args;
}; // struct __command_arguments

struct __command_result
{
	int _rpl;
	int _len;
	char** _args;

	__command_result(int rpl, ...) :
		_rpl(rpl),
		_len(0),
		_args(NULL)
	{
		va_list ap;
		std::vector
		char const* arg;

		va_start(ap, rpl);
		while (true)
		{
			arg = va_arg(ap, char const*);
			if (arg == NULL)
				break;
		}
		va_end(ap);
	}
}; // struct __command_result

typedef __command_result (*__command_executor)(__command_arguments const&);

struct __command
{
	std::string const _name;
	__command_executor _exec;
}; // struct __command

__command_result command_pass(__command_arguments const& args);
__command_result command_nick(__command_arguments const& args);
__command_result command_user(__command_arguments const& args);
__command_result command_oper(__command_arguments const& args);
__command_result command_quit(__command_arguments const& args);
__command_result command_join(__command_arguments const& args);
__command_result command_part(__command_arguments const& args);
__command_result command_privmsg(__command_arguments const& args);
__command_result command_notice(__command_arguments const& args);
} // namespace irc

#endif // COMMAND_H
