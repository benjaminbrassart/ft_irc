/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 13:57:53 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/14 17:12:21 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdint.h>
# include <arpa/inet.h>

namespace irc
{
::uint16_t parse_port(char const* s);
::in_addr_t parse_address(char const* s);
} // namespace irc

#endif
