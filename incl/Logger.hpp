/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Logger.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 04:54:38 by bbrassar          #+#    #+#             */
/*   Updated: 2022/12/05 15:43:35 by bbrassar         ###   ########.fr       */
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
	FATAL,
};

class Logger
{
private:
	LogLevel _level;

public:
	explicit Logger(LogLevel level);
	~Logger();

public:
	void log(LogLevel level, std::string const& message);
};

#endif // LOGGER_HPP
