/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InputContext.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 13:38:11 by bbrassar          #+#    #+#             */
/*   Updated: 2022/12/17 13:40:34 by bbrassar         ###   ########.fr       */
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

	std::string message;
	Args& args;

	InputContext(std::string const& message, Args& args);
	~InputContext();
};