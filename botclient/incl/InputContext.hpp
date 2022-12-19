/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InputContext.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 13:38:11 by bbrassar          #+#    #+#             */
/*   Updated: 2022/12/19 20:24:47 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <deque>
#include <string>

struct InputContext;
class Bot;

typedef void (Bot::*InputHandler)(InputContext&);

struct InputContext
{
	typedef std::deque< std::string > Args;

	std::string sender;
	std::string message;
	Args& args;

	InputContext(std::string const& sender, std::string const& message, Args& args);
	~InputContext();

	static Args split(std::string const& line);
};
