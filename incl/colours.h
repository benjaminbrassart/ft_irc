/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colours.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estoffel <estoffel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 03:50:25 by lrandria          #+#    #+#             */
/*   Updated: 2022/11/16 16:12:38 by estoffel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOURS_H
# define COLOURS_H

/* normal */
# define RED			"\e[0;31m"
# define L_RED			"\e[0;38;5;9m"
# define GREEN			"\e[0;32m"
# define D_GREEN		"\e[0;38;5;22m"
# define V_GREEN		"\e[0;38;5;82m"
# define P_GREEN		"\e[0;38;5;23m"
# define BLUE			"\e[0;34m"
# define V_BLUE			"\e[0;38;5;27m"
# define P_BLUE			"\e[0;38;5;24m"
# define CYAN			"\e[0;36m"
# define V_CYAN			"\e[0;38;5;44m"
# define MAGENTA		"\e[0;35m"
# define PURPLE			"\e[0;38;5;93m"
# define LILAC			"\e[0;38;5;13m"
# define PINK			"\e[0;38;5;199m"
# define YELLOW			"\e[0;33m"
# define L_YELLOW		"\e[0;38;5;191m"
# define BLACK			"\e[0;30m"
# define WHITE			"\e[0;37m"
# define GRAY			"\e[0;38;5;8m"
# define L_GRAY			"\e[0;38;5;245m"
# define ORANGE			"\e[0;38;5;166m"
# define V_ORANGE		"\e[0;38;5;202m"

/* bold */
# define B_RED			"\e[1;31m"
# define B_GREEN		"\e[1;32m"
# define B_BLUE			"\e[1;34m"
# define B_CYAN			"\e[1;36m"
# define B_MAGENTA		"\e[1;35m"
# define B_YELLOW		"\e[1;33m"
# define B_BLACK		"\e[1;30m"
# define B_WHITE		"\e[1;37m"

/* underline*/
# define U_RED			"\e[4;31m"
# define U_GREEN		"\e[4;32m"
# define U_BLUE			"\e[4;34m"
# define U_CYAN			"\e[4;36m"
# define U_MAGENTA		"\e[4;35m"
# define U_YELLOW		"\e[4;33m"
# define U_BLACK		"\e[4;30m"
# define U_WHITE		"\e[4;37m"

/* high intensity */
# define H_RED			"\e[0;91m"
# define H_GREEN		"\e[0;92m"
# define H_BLUE			"\e[0;94m"
# define H_CYAN			"\e[0;96m"
# define H_MAGENTA		"\e[0;95m"
# define H_YELLOW		"\e[0;93m"
# define H_BLACK		"\e[0;90m"
# define H_WHITE		"\e[0;97m"

/* bold high intensity */
# define BH_BLACK		"\e[1;90m"
# define BH_RED			"\e[1;91m"
# define BH_GREEN		"\e[1;92m"
# define BH_YELLOW		"\e[1;93m"
# define BH_BLUE		"\e[1;94m"
# define BH_MAGENTA		"\e[1;95m"
# define BH_CYAN		"\e[1;96m"
# define BH_WHITE		"\e[1;97m"

									/*** BACKGROUND ***/

/* normal */
# define RED_BG			"\e[41m"
# define GREEN_BG		"\e[42m"
# define BLUE_BG		"\e[44m"
# define CYAN_BG		"\e[46m"
# define MAGENTA_BG		"\e[45m"
# define YELLOW_BG		"\e[43m"
# define BLACK_BG		"\e[40m"
# define WHITE_BG		"\e[47m"

/* high intensity*/
# define H_RED_BG		"\e[0;101m"
# define H_GREEN_BG		"\e[0;102m"
# define H_BLUE_BG		"\e[0;104m"
# define H_CYAN_BG		"\e[0;106m"
# define H_MAGENTA_BG	"\e[0;105m"
# define H_YELLOW_BG	"\e[0;103m"
# define H_BLACK_BG		"\e[0;100m"
# define H_WHITE_BG		"\e[0;107m"

/* reset */
# define END			"\e[0m"

#endif
