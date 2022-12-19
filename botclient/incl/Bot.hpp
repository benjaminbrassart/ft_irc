/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 07:52:19 by estoffel          #+#    #+#             */
/*   Updated: 2022/12/19 00:50:49 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOT_HPP
# define BOT_HPP

# include "MessageRegistry.hpp"
# include "InputContext.hpp"
# include <map>
# include <netdb.h>
# include <stdexcept>
# include <string>
# include <sys/types.h>
# include <sys/socket.h>

struct InputContext;

class Bot {

	public:
		typedef std::map< std::string, InputHandler > InputMap;

		static std::string const PREFIX;

	private:
		int clientFd;

	public:
		MessageRegistry messageRegistry;
		InputMap inputMap;

		Bot();
		Bot(Bot const& cpy);
		~Bot();

		Bot &operator=(Bot const& asgn);

		void	connectClient(const char* hostname, const char* port);

		bool	checkSimilarMessage(std::string const& message);

		void	receive();
		void	send(std::string const& message);
		void	respond(std::string const& target, std::string const& message);

		void	onInvite(InputContext& ctx);
		void	onError(InputContext& ctx);
		void	onPart(InputContext& ctx);
		void	onMessage(InputContext& ctx);

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
};

#endif
