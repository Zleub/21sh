NAME = 21sh
LIBNAME = libsh.a

SRC = $(shell find src -name '*\.c')
OBJ = $(subst .c,.o, $(SRC))

CC = clang
HEADDIR ?= -I$(PWD)/inc -I$(PWD)/libft/inc
CFLAGS ?= -Wall -Werror -Wextra $(HEADDIR)
LDFLAGS ?= -lft -Llibft -lsh -L.

all: libft $(LIBNAME) $(NAME) main.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(NAME) main.c

$(LIBNAME): $(OBJ)
	ar rc $@ $^
	ranlib $@

libft:
	make -C libft

ft_printf:
	make -C ft_printf

clean:
	make -C libft clean
	make -C ft_printf clean
	rm -rf test
	rm -rf $(OBJ)

fclean:
	make -C libft fclean
	make -C ft_printf fclean
	rm -rf test
	rm -rf $(OBJ)
	rm -rf $(NAME)

re: fclean libft ft_printf
	make all

.PHONY: all $(LIBNAME) $(NAME) clean fclean re libft ft_printf
