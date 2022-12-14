# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: parallels <parallels@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/10 00:50:14 by estoffel          #+#    #+#              #
#    Updated: 2022/12/14 03:14:13 by parallels        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	ircserv

CC		=	c++

DEFINES += -D_GLIBCXX_DEBUG

FLAGS	=	-Wall -Wextra -Werror -Iincl -g3 -MMD -MP -std=c++98 $(DEFINES)

# main
SRC		= main.cpp

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
	@printf "\n"
	@printf "\n"
	@printf "   🌼\033[1;97m I R C S E R V  C R E A T E D  W I T H  S U C C E S S 🌼\e[0m\n"
	@printf "\n"
	@printf "				x\n"
	@printf "\n"
	@printf "		✨	~ \033[1;97mBen Enora Liana\e[0m ~	✨\n"
	@printf "\n"
	@printf "\n"

clean:
	$(RM) obj/
	@printf "\n"
	@printf "💧\033[1;97m E V E R Y T H I N G  I S  C L E A N E D 💧\e[0m\n"
	@printf "\n"

fclean:
	$(RM) obj/
	$(RM) $(NAME)
	@printf "\n"
	@printf "💧\033[1;97m E V E R Y T H I N G  I S  C L E A N E D 💧\e[0m\n"
	@printf "\n"

re: fclean all

.PHONY: all clean fclean re
