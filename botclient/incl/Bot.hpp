/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 07:52:19 by estoffel          #+#    #+#             */
/*   Updated: 2022/12/17 15:22:38 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOT_HPP
# define BOT_HPP

# include <sys/types.h>
# include <sys/socket.h>
# include <netdb.h>
# include <stdexcept>
# include <string>

struct InputContext;

class Bot {

	public:
		Bot();
		Bot(Bot const&);
		~Bot();

		Bot &operator=(Bot const&);

		void	connexionClient();

		void onInvite(InputContext& ctx);
		void onError(InputContext& ctx);
		void onPart(InputContext& ctx);
		void onMessage(InputContext& ctx);

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
