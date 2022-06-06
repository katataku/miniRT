NAME = miniRT
CC = gcc
CFLAGS = -Wall -Wextra -Werror -MMD -MP
SRCS := main.c
SRCS += $(addprefix srcs/io/, \
		read_ambient.c read_camera.c read_cylinder.c read_file.c read_light.c read_plane.c read_sphere.c util.c validate_arg.c)
SRCS += $(addprefix srcs/objects/, \
		object.c plane.c sphere.c cylinder.c cylinder_utils.c calc_lambert_cos_cylinder.c rt.c camera.c screen.c)
SRCS += $(addprefix srcs/vector3/, \
		add.c cos_of_angles.c inner_product.c multiply.c norm.c normalize.c outer_product.c print.c sub.c  vector3.c calc_dist.c)
SRCS += $(addprefix srcs/xsyscall/, \
		xclose.c xfork.c xopen.c xpipe.c xwaitpid.c xdup2.c)
SRCS += $(addprefix srcs/xlibft/, \
		ft_xcalloc.c ft_xlstnew.c ft_xsplit.c ft_xstrdup.c ft_xstrjoin.c)
SRCS += $(addprefix srcs/utils/, \
		ft_atod.c error.c mlx_hooks.c mlx_util.c util.c validate_double.c validate_integer.c)
OBJS = $(SRCS:%.c=%.o)
DEPENDS	= $(OBJS:.o=.d)
LIBS = -lft -Llibft -lm -lX11 -lXext
INCS = -Ilibft/includes -Iincludes -Imlx
LIBFT = libft/libft.a
MLX = mlx/libmlx.a

# switch include libs depends on the OS types.
UNAME = $(shell uname)
ifeq ($(UNAME), Darwin)
LIBS += -Lmlx -lmlx_Darwin -L/usr/X11R6/lib -framework OpenGL -framework AppKit
else
LIBS += -Imlx_linux -L/usr/lib -lm
endif

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	$(CC) -o $(NAME) $(CFLAGS) $(OBJS) $(MLX) $(LIBS)

$(LIBFT):
	make -C libft

$(MLX):
	make -C mlx

%.o: %.c
	$(CC) $(CFLAGS) $(INCS) -o $@ -c $<

all: $(NAME)

fclean: clean
	make fclean -C libft
	$(RM) $(NAME)

clean:
	make clean -C libft
	make clean -C mlx
	$(RM) $(OBJS) $(DEPENDS)

re: fclean all

.PHONY: all fclean clean re
-include $(DEPENDS)
# DELETE #
.PHONY: test
test:
	make -C tests
ng-test: $(NAME)
	bash tests/test.sh
.PHONY: run
run: $(NAME)
	./miniRT rt_files/minimalist.rt
.PHONY: sphere
sphere: $(NAME)
	./miniRT rt_files/minimam_sphere.rt
.PHONY: plane
plane: $(NAME)
	./miniRT rt_files/minimam_plane.rt
.PHONY: cy
cy: $(NAME)
	./miniRT rt_files/minimam_cylinder.rt
