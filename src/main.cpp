/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estoffel <estoffel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 00:55:38 by estoffel          #+#    #+#             */
/*   Updated: 2022/11/10 01:52:10 by estoffel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//./ircserv <port> <password>
int	main(int ac, char **av) {

	if (ac != 3) {
		std::cerr << "Wrong number of arguments -> \"./ircserv <port> <password>\"\n";
		return 1;
	}
	return 0;
}