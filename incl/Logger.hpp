/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Logger.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 04:54:38 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/29 21:48:33 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOGGER_HPP
# define LOGGER_HPP

# include <string>

enum LogLevel
{
	DEBUG,
	INFO,
	NOTICE,
	WARNING,
	ERROR,
};

class Logger
{
public:

public:
	LogLevel level;

public:
	Logger(LogLevel level);
	~Logger();

public:
	void log(LogLevel level, std::string const& message);
};

#endif // LOGGER_HPP
