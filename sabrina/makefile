# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sperrin <sperrin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/23 14:22:50 by sperrin           #+#    #+#              #
#    Updated: 2020/10/21 12:55:15 by sperrin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =  src/main.c \
		src/ray.c \
		src/map.c \
		src/key_hook.c \
		src/init.c \
		src/img_put.c \
		src/draw.c \
		src/clean.c \
		src/bit_map.c \
		src/map_check.c \
		src/sprite.c \
		src/spawn.c \
		src/parse.c \
		src/error.c \
		src/res.c \
		src/tools.c
		
CC = gcc -g
CFLAGS = -Wall -Werror -Wextra
NAME = cub3d

OBJS = $(SRCS:%.c=%.o)

all: $(NAME)

$(NAME):$(OBJS)
	$(MAKE) -C libft
	$(MAKE) -C minilibx_opengl_20191021
	$(CC) $(CFLAGS) $(OBJS) ./libft/libft.a -L minilibx_opengl_20191021 -lmlx -framework OpenGL -framework AppKit -o $(NAME) 

clean:
	rm -f $(OBJS)
	
fclean:clean
	rm -f $(NAME)
	rm -f bitmap.bmp

.PHONY: all clean fclean
