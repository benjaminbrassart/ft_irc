/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estoffel <estoffel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 07:52:19 by estoffel          #+#    #+#             */
/*   Updated: 2022/12/17 14:53:04 by estoffel         ###   ########.fr       */
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

		void	connectClient(const char*, const char*);

		class IOException : public std::exception
		{
		private:
			std::string _reason;

		public:
			IOException(std::string const& syscallName, int errnum);
			IOException(std::string const& syscallName, std::string const& msg);
			~IOException() throw();

		public:
			char const* what() const throw();
		}; // class IOException

	private:
		int	clientFd;
};

#endif