NAME = minirt
CC = gcc
CFLAGS = -Wall -Wextra -Werror
XSYSCALL_SRCS = $(addprefix srcs/xsyscall/, \
		xclose.c xfork.c xopen.c xpipe.c xwaitpid.c xdup2.c \
		)
XLIBFT_SRCS = $(addprefix srcs/xlibft/, \
		ft_xcalloc.c ft_xlstnew.c ft_xsplit.c ft_xstrdup.c ft_xstrjoin.c \
		)
UTILS_SRCS = $(addprefix srcs/utils/, \
		error.c util.c \
		)
SRCS = main.c $(XSYSCALL_SRCS) $(XLIBFT_SRCS) $(UTILS_SRCS)
OBJS = $(SRCS:%.c=%.o)
LIBS = -lft -Llibft
INCS = -Ilibft/includes -Iincludes
LIBFT = libft/libft.a

$(NAME): $(LIBFT) $(OBJS)
	$(CC) -o $(NAME) $(CFLAGS) $(OBJS) $(LIBS)

$(LIBFT):
	make -C libft

%.o: %.c
	$(CC) $(CFLAGS) $(INCS) -o $@ -c $<

all: $(NAME)

fclean: clean
	make fclean -C libft
	$(RM) $(NAME) $(NAME_BONUS)

clean:
	make clean -C libft
	$(RM) $(OBJS) $(OBJS_BONUS)

re: fclean all

.PHONY: all fclean clean re

.PHONY: test
test: ultest itest

.PHONY: ltest
ltest: ultest iltest

.PHONY: utest
utest:
	make -C tests

.PHONY: ultest
ultest:
	make -C tests ltest
