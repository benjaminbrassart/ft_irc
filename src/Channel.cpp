/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 20:12:48 by lrandria          #+#    #+#             */
/*   Updated: 2022/11/15 20:23:07 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/Channel.hpp"

/* ==========================================================================
								COPLIEN FORM 
   ========================================================================== */
   
Channel::Channel() {
	std::cout << BLUE << "Channel default constructor called!\n" RESET;
}

Channel::Channel(Channel const &src) {
	
	std::cout << BLUE "Channel copy constructor called!\n" RESET;
	*this = src;
}

Channel::~Channel() {
	std::cout << RED "Channel destructor called!\n" RESET;
}

Channel  &Channel::operator=(Channel const &rhs) {
	
	std::cout << BLUE "Channel assignment operator called!\n" RESET;
	if (this != &rhs) {
	
		server = rhs.server;
		topic = rhs.topic;
		password = rhs.password;
		_clients = rhs._clients;
	}
	return (*this);
}

/* ==========================================================================
								MEMBER FUNCTIONS 
   ========================================================================== */

void		Channel::cmdJoin(std::string channel, std::string key) {
	
	
}

void		Channel::cmdPart(std::string channel, std::string reason) {
	
	
}

void		Channel::cmdTopic(std::string channel, std::string topic) {
	
	
}

void		Channel::cmdNames(std::string channel) {
	
	
}

void		Channel::cmdList(std::string channel) {
	
	
} //optional "elist" param

void		Channel::cmdInvite(std::string nickname, std::string channel) {
	
	
}

void		Channel::cmdKick(std::string channel, std::string user) {
	
	
}

