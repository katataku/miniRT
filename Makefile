NAME = minirt
CC = gcc
CFLAGS = -Wall -Wextra -Werror -MMD -MP
IO_SRCS = $(addprefix srcs/io/, \
		object.c plane.c sphere.c \
		)
OBJECTS_SRCS = $(addprefix srcs/objects/, \
		read_ambient.c read_camera.c read_cylinder.c read_file.c read_light.c read_plane.c read_sphere.c util.c validate_arg.c \
		)
VECTOR3_SRCS = $(addprefix srcs/vector3/, \
		add.c cos_of_angles.c inner_product.c multiply.c norm.c normalize.c outer_product.c print.c sub.c  vector3.c \
		)
XSYSCALL_SRCS = $(addprefix srcs/xsyscall/, \
		xclose.c xfork.c xopen.c xpipe.c xwaitpid.c xdup2.c \
		)
XLIBFT_SRCS = $(addprefix srcs/xlibft/, \
		ft_xcalloc.c ft_xlstnew.c ft_xsplit.c ft_xstrdup.c ft_xstrjoin.c \
		)
UTILS_SRCS = $(addprefix srcs/utils/, \
		error.c mlx_util.c util.c \
		)
SRCS = main.c $(IO_SRCS) $(VECTOR3_SRCS) $(XSYSCALL_SRCS) $(XLIBFT_SRCS) $(UTILS_SRCS)
OBJS = $(SRCS:%.c=%.o)
DEPENDS	= $(OBJS:.o=.d)
LIBS = -lft -Llibft -lm
INCS = -Ilibft/includes -Iincludes -Imlx
MLX_FOR_MAC = -Lmlx -L/usr/X11R6/lib -lX11 -lXext -lmlx_Darwin -framework OpenGL -framework AppKit
LIBFT = libft/libft.a
MLX = mlx/libmlx.a

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	$(CC) -o $(NAME) $(CFLAGS) $(OBJS) $(MLX_FOR_MAC) $(LIBS)

$(LIBFT):
	make -C libft

$(MLX):
	make -C mlx

%.o: %.c
	$(CC) $(CFLAGS) $(INCS)  -o $@ -c $<

all: $(NAME)

fclean: clean
	make fclean -C libft
	$(RM) $(NAME) $(NAME_BONUS)

clean:
	make clean -C libft
	make clean -C mlx
	$(RM) $(OBJS) $(OBJS_BONUS) $(DEPENDS)

re: fclean all

.PHONY: all fclean clean re
-include $(DEPENDS)
# DELETE #
.PHONY: test
test:
	make -C tests
.PHONY: run
run:
	./minirt rt_files/minimam_sphere.rt
.PHONY: sphere
sphere:
	./minirt rt_files/minimam_sphere.rt
.PHONY: plane
plane:
	./minirt rt_files/minimam_plane.rt
