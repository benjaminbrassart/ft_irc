/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:04:37 by bbrassar          #+#    #+#             */
/*   Updated: 2022/12/02 10:01:04 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

# define SERVER_NAME "ft_ble"

# define VERSION_MAJOR 1
# define VERSION_MINOR 0
# define VERSION_PATCH 0

# define _STR(S) #S
# define STR(S) _STR(S)

# define VERSION "" STR(VERSION_MAJOR) "." STR(VERSION_MINOR) "." STR(VERSION_PATCH)

#endif // CONFIG_H
