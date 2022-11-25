/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Recipient.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 09:31:00 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/25 09:31:55 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Recipient.hpp"

Recipient::Recipient(Server& server) :
	server(&server)
{}

Recipient::~Recipient()
{}
