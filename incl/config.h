/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:04:37 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/21 13:33:07 by bbrassar         ###   ########.fr       */
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

# ifdef VERSION_COMMIT
#  define VERSION_SUFFIX "-" STR(VERSION_COMMIT)
# else
#  define VERSION_SUFFIX "(unknown)"
# endif

# ifndef BUILD_DATE
#  define BUILD_DATE "(unknown)"
# endif

# define VERSION "" STR(VERSION_MAJOR) "." STR(VERSION_MINOR) "." STR(VERSION_PATCH) VERSION_SUFFIX

#endif // CONFIG_H
