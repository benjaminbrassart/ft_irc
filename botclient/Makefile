# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: estoffel <estoffel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/17 08:09:48 by estoffel          #+#    #+#              #
#    Updated: 2022/12/17 08:13:40 by estoffel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	bot

CC		=	c++

DEFINES += -D_GLIBCXX_DEBUG

FLAGS	=	-Wall -Wextra -Werror -Iincl -g3 -MMD -MP -std=c++98 $(DEFINES)

# main
SRC		= main.cpp

# # utils

# SRC		+= utils/NameUtils.cpp

# classes
SRC		+= Bot.cpp

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
