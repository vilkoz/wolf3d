# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vrybalko <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/23 14:08:11 by vrybalko          #+#    #+#              #
#    Updated: 2017/02/28 21:04:33 by vrybalko         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d

IDIR = includes/

VPATH = src:includes

BIN_DIR = bin/

FLAGS = -Wall -Wextra -Werror -I$(IDIR) -g

FLAGS_MLX = -lmlx -framework OpenGl -framework AppKit

FLAGS_X11 = -lmlx -lXext -lX11 -lm

LIB = libft/libft.a

SRCS = main.c					\
	   ft_img_px_put.c			\
	   ft_mlx_events.c			\
	   ft_mlx_init.c			\
	   ft_draw_line.c			\
	   ft_mlx_helpers.c			\
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
	   ft_menu.c				\
	   ft_game_mode_hooks.c


BINS = $(addprefix $(BIN_DIR), $(SRCS:.c=.o))

all: $(NAME)

$(NAME): $(BINS)
	make -C libft/
	gcc -o $(NAME) $(BINS) $(FLAGS) $(FLAGS_MLX) $(LIB)

$(BIN_DIR)%.o: %.c
	gcc $(FLAGS) -c -o $@ $<

clean:
	make -C libft/ clean
	/bin/rm -f $(BINS)

fclean: clean
	make -C libft/ fclean
	/bin/rm -f $(NAME)

re: fclean all

f: all
	./$(NAME) res/test.map

r: re f
