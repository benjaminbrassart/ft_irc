/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 13:33:18 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/14 17:17:15 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

#include <stdint.h>
#include <ctime>
#include <string>
#include <netinet/in.h>
#include <sys/epoll.h>

namespace irc
{
class server
{
	private:
	// parameters
	uint16_t _port;
	std::string _password;

	// time
	std::time_t _start_time;

	// socket
	int _sock_fd;
	::sockaddr_in _addr;

	// epoll
	epoll_event _event;
	int _epoll_fd;

	public:
	server();
	server(::uint16_t port, std::string const& password);
	server(server const& x);
	server& operator=(server const& x);
	~server();

	public:
	/**
	 * Start the server
	 *
	 * @throws irc::io_exception if a system call fails
	 *
	 * @see socket(2)
	 * @see bind(2)
	 * @see listen(2)
	 * @see accept(2)
	 * @see epoll(2)
	 */
	void start();

	/**
	 * Check if a supplied password is correct
	 *
	 * @param password the password to check
	 * @return true if the passwords match, false otherwise
	 */
	bool check_password(std::string const& password);

	private:
	void __socket();
	void __epoll();
	void __setup_addr();
	void __bind();
	void __listen();
	void __splash();
	void __run();
	void __cleanup();

	void __add_fd(int fd);
	void __remove_fd(int fd);

	private:
	static std::string __date_str();

}; // class server
} // namespace irc

#endif // SERVER_HPP
