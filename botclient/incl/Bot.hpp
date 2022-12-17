/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estoffel <estoffel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 07:52:19 by estoffel          #+#    #+#             */
/*   Updated: 2022/12/17 09:05:18 by estoffel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOT_HPP
# define BOT_HPP

# include <sys/types.h>
# include <sys/socket.h>
# include <netdb.h>
# include <stdexcept>
# include <string>


class Bot {

	public:
		Bot();
		Bot(Bot const&);
		~Bot();

		Bot &operator=(Bot const&);

		void	connexionClient();

		class IOException : public std::exception
		{
		private:
			std::string _reason;

		public:
			IOException(std::string const& syscallName, int errnum);
			~IOException() throw();

		public:
			char const* what() const throw();
		}; // class IOException

	private:
};

#endif