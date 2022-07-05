# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/05 13:40:38 by ademurge          #+#    #+#              #
#    Updated: 2022/07/05 13:41:52 by ademurge         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BLACK		= $(shell tput -Txterm setaf 0)
RED			= $(shell tput -Txterm setaf 1)
GREEN		= $(shell tput -Txterm setaf 2)
YELLOW		= $(shell tput -Txterm setaf 3)
LIGHTPURPLE	= $(shell tput -Txterm setaf 4)
PURPLE		= $(shell tput -Txterm setaf 5)
BLUE		= $(shell tput -Txterm setaf 6)
WHITE		= $(shell tput -Txterm setaf 7)
RESET		= $(shell tput -Txterm sgr0)

SRC			=

LIBFT		=

NAME		= philo

CFLAGS		= -Wall -Wextra -Werror

all:		$(NAME)

$(NAME):
			@gcc ${CFLAGS} ${SRC} ${LIBFT} -o ${NAME}
			@echo "$(GREEN)********** Compiled. $(RESET)"

clean:
			@rm -f ${OBJS}
			@echo "$(PURPLE)********** Objects removed. $(RESET)"

fclean:		clean
			@rm -f $(NAME)
			@echo "$(LIGHTPURPLE)********** Executable removed. $(RESET)"

re:			fclean all

.PHONY:		all clean fclean re bonus