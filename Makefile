# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/17 08:15:01 by estoffel          #+#    #+#              #
#    Updated: 2022/12/18 19:37:25 by bbrassar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

all: server client
	@printf "\n"
	@printf "\n"
	@printf "   🌼\033[1;97m I R C S E R V  C R E A T E D  W I T H  S U C C E S S 🌼\e[0m\n"
	@printf "\n"
	@printf "				x\n"
	@printf "\n"
	@printf "		✨	~ \033[1;97mBen Enora Liana\e[0m ~	✨\n"
	@printf "\n"
	@printf "\n"

server:
	$(MAKE) -C ./ircserver all $(strip $(MAKEFLAGS))

client:
	$(MAKE) -C ./botclient all $(strip $(MAKEFLAGS))

clean:
	$(MAKE) -C ./botclient clean
	$(MAKE) -C ./ircserver clean
	@printf "\n"
	@printf "💧\033[1;97m E V E R Y T H I N G  I S  C L E A N E D 💧\e[0m\n"
	@printf "\n"

fclean:
	$(MAKE) -C ./botclient fclean
	$(MAKE) -C ./ircserver fclean
	@printf "\n"
	@printf "💧\033[1;97m E V E R Y T H I N G  I S  C L E A N E D 💧\e[0m\n"
	@printf "\n"

re: fclean all

.PHONY: all clean fclean re client server
