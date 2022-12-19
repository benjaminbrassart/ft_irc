/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InputContext.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 13:45:29 by bbrassar          #+#    #+#             */
/*   Updated: 2022/12/17 13:46:04 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "InputContext.hpp"

InputContext::InputContext(std::string const& message, Args& args) :
	message(message),
	args(args)
{}

InputContext::~InputContext()
{}
