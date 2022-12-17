# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: estoffel <estoffel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/10 00:50:14 by estoffel          #+#    #+#              #
#    Updated: 2022/12/17 08:17:01 by estoffel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	ircserv

CC		=	c++

DEFINES += -D_GLIBCXX_DEBUG

FLAGS	=	-Wall -Wextra -Werror -Iincl -g3 -MMD -MP -std=c++98 $(DEFINES)

# main
SRC		= main.cpp

# utils

SRC		+= utils/NameUtils.cpp

# classes
SRC		+= class/NicknameManager.cpp
SRC		+= class/ClientManager.cpp
SRC		+= class/ChannelManager.cpp
SRC		+= class/ConnectionManager.cpp
SRC		+= class/exception/IOException.cpp

SRC		+= Recipient.cpp
SRC		+= Client.cpp
SRC		+= CommandContext.cpp
SRC		+= Channel.cpp
SRC		+= Server.cpp
SRC		+= CommandMap.cpp
SRC		+= Reply.cpp
SRC		+= OperatorEntry.cpp
SRC		+= wildcard.cpp
SRC		+= Logger.cpp

# commands
SRC		+= cmds/cmd_user.cpp
SRC		+= cmds/cmd_nick.cpp
SRC		+= cmds/cmd_pass.cpp
SRC		+= cmds/cmd_quit.cpp
SRC		+= cmds/cmd_part.cpp
SRC		+= cmds/cmd_join.cpp
SRC		+= cmds/cmd_motd.cpp
SRC		+= cmds/cmd_oper.cpp
SRC		+= cmds/cmd_die.cpp
SRC		+= cmds/cmd_kill.cpp
SRC		+= cmds/cmd_ping.cpp
SRC		+= cmds/cmd_mode.cpp
SRC		+= cmds/cmd_privmsg.cpp
SRC		+= cmds/cmd_restart.cpp
SRC		+= cmds/cmd_notice.cpp
SRC		+= cmds/cmd_topic.cpp
SRC		+= cmds/cmd_kick.cpp
SRC		+= cmds/cmd_list.cpp
SRC		+= cmds/cmd_names.cpp
SRC		+= cmds/cmd_invite.cpp

OBJ		:=	$(addprefix ./obj/,$(SRC:%.cpp=%.o))

DEP		=	$(OBJ:%.o=%.d)

RM		=	rm -rf

all: $(NAME)

-include $(DEP)

./obj/%.o: ./src/%.cpp
	@mkdir -p $(@D)
	$(CC) $(FLAGS) -o $@ -c $<

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ)

clean:
	$(RM) obj/

fclean:
	$(RM) obj/
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
