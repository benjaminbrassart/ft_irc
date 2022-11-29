/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Logger.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 05:03:51 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/29 07:46:34 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Logger.hpp"
#include "colours.h"
#include <iostream>
#include <iomanip>

static std::string __now()
{
	return "";
}

Logger::Logger(Logger::Level level) :
	level(level)
{}

Logger::~Logger()
{}

void Logger::log(Logger::Level level, std::string const& message)
{
	std::string color;
	std::string levelName;
	std::string time;
	std::ostream* stream_p;

	if (level < this->level)
		return;

	switch (level)
	{
		case DEBUG:
			color = GREEN;
			levelName = "DEBUG";
			stream_p = &std::cout;
			break;
		case INFO:
			color = WHITE;
			levelName = "INFO";
			stream_p = &std::cout;
			break;
		case NOTICE:
			color = CYAN;
			levelName = "NOTICE";
			stream_p = &std::cout;
			break;
		case WARNING:
			color = ORANGE;
			levelName = "WARNING";
			stream_p = &std::cerr;
			break;
		case ERROR:
			color = RED;
			levelName = "ERROR";
			stream_p = &std::cerr;
			break;
		default: return;
	}

	*stream_p
		<< "[" << __now() << "] "
		<< color << std::setw(7) << levelName << END << " |"
		<< message << '\n';
}