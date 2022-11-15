# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/08 07:03:27 by bbrassar          #+#    #+#              #
#    Updated: 2022/11/14 18:43:44 by bbrassar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ircserv

# ---------------------------------------------------------------------------- #

CXX = c++
CXXFLAGS += -Wall
CXXFLAGS += -Werror
CXXFLAGS += -Wextra
CXXFLAGS += -Wshadow
CXXFLAGS += -std=c++98
CXXFLAGS += -c
CXXFLAGS += -g3
CXXFLAGS += -I .
CXXFLAGS += -I $(DIR_SRC)

RM = rm -f

# ---------------------------------------------------------------------------- #

DIR_SRC = src
DIR_OBJ = obj

# ---------------------------------------------------------------------------- #

SRC += main.cpp
SRC += parser.cpp
SRC += class/server.cpp

OBJ = $(SRC:%.cpp=$(DIR_OBJ)/%.o)
DEP = $(OBJ:.o=.d)

# ---------------------------------------------------------------------------- #

$(NAME): $(OBJ)
	$(CXX) $^ -o $@

$(OBJ): $(DIR_OBJ)/%.o: $(DIR_SRC)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $< -o $@

-include $(DEP)

# ---------------------------------------------------------------------------- #

all: $(NAME)

clean:
	$(RM) -r $(DIR_OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
