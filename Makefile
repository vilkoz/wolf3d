# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vrybalko <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/23 14:08:11 by vrybalko          #+#    #+#              #
#    Updated: 2017/03/26 18:51:57 by vrybalko         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d

IDIR = includes/

VPATH = src:includes

BIN_DIR = bin/

MLX_DIR = minilibx/

MLX_DIR_MAC = minilibx_macos/

FLAGS = -Wall -Wextra -Werror -I$(IDIR) -g -fopenmp

FLAGS_MLX = -lmlx -framework OpenGl -framework AppKit

FLAGS_X11 = -lmlx -lXext -lX11 -lm

LIB = libft/libft.a $(MLX_DIR)/libmlx.a

SRCS = main.c					\
	   ft_img_px_put.c			\
	   ft_mlx_events.c			\
	   ft_mlx_init.c			\
	   ft_mlx_init1.c			\
	   ft_draw_line.c			\
	   ft_mlx_helpers.c			\
	   ft_mlx_helpers1.c		\
	   ft_hooks.c				\
	   ft_read_map.c			\
	   ft_raycast.c				\
	   ft_load_tex.c			\
	   ft_textures.c			\
	   ft_sprites.c				\
	   ft_shades.c				\
	   ft_doors.c				\
	   ft_enemies.c				\
	   ft_put_info.c			\
	   ft_put_info1.c			\
	   ft_menu.c				\
	   ft_game_mode_hooks.c		\
	   ft_shoot.c				\
	   ft_load_gif.c			\
	   ft_pickups.c


BINS = $(addprefix $(BIN_DIR), $(SRCS:.c=.o))

all: lib $(NAME)

lib:
	make -C $(MLX_DIR)
	make -C libft/

libclean:
	make -C $(MLX_DIR) clean
	make -C libft/ clean

libfclean:
	make -C libft/ fclean

$(NAME): $(BINS)
	gcc -o $(NAME) $(BINS) $(FLAGS) $(FLAGS_X11) $(LIB) -L $(MLX_DIR) \
		-I $(MLX_DIR)

$(BIN_DIR)%.o: %.c
	gcc $(FLAGS) -c -o $@ $<

clean: libclean
	/bin/rm -f $(BINS)

fclean: libfclean clean
	/bin/rm -f $(NAME)

re: fclean all

f: all
	./$(NAME) res/test.map

r: re f
