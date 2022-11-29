/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Logger.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 04:54:38 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/25 05:04:17 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOGGER_HPP
# define LOGGER_HPP

# include <string>

class Logger
{
public:
	enum Level
	{
		DEBUG,
		INFO,
		NOTICE,
		WARNING,
		ERROR,
	};

public:
	Logger::Level level;

public:
	Logger(Logger::Level level);
	~Logger();

public:
	void log(Logger::Level level, std::string const& message);
};

#endif // LOGGER_HPP
