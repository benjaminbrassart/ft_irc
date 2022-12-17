/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estoffel <estoffel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 07:57:48 by estoffel          #+#    #+#             */
/*   Updated: 2022/12/17 15:06:12 by estoffel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bot.hpp"
#include <iostream>

int	main(int ac, char **av) {

	Bot	Mee1;
	
	if (ac != 3) {
		std::cerr << "Wrong number of arguments" << std::endl;
		return 1;
	}
	try
	{
		Mee1.connectClient(av[1], av[2]);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return 1;
	}
	return 0;
}