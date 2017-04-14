# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adebray <adebray@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2013/11/19 11:21:22 by adebray           #+#    #+#              #
#    Updated: 2016/04/02 15:58:53 by adebray          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libft.a

HEADDIR		?= inc
CC			?= clang
CFLAGS		?= -I $(HEADDIR) -Werror -Wall -Wextra -Wuninitialized -O3

SRC			= $(shell find . -name "*.c")
OBJ			= $(subst .c,.o,$(SRC))

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $@ $^
	ranlib $@

clean:
	rm -f $(OBJ)

fclean:
	rm -f $(OBJ)
	rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re
