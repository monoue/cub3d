CC = gcc
CFLAGS = -Wall -Werror -Wextra
NAME = cub3D

SRCS = cub3d.c texture_set.c free_utils.c\
	maps_get.c texture.c \
	map_check.c texture_etc.c \
	inits.c sprites_etc.c save.c maps.c sprites.c \
	moves.c textures_1.c maps_getcolor.c errors.c rolls.c \
	hit_walls.c keys.c \
	./get_next_line/get_next_line.c \
	ft_atoi.c ft_isdigit.c ft_memcpy.c ft_split.c ft_strdup.c ft_strncmp.c ft_strnstr.c \
	ft_strlen.c ft_strchr.c ft_strjoin.c

OBJS = $(SRCS:%.c=%.o)

UNAME_S := $(shell uname)
ifeq ($(UNAME_S),Linux)
	PLATFORM := LINUX
endif
ifeq ($(UNAME_S),Darwin)
	PLATFORM := MACOS
endif
ifeq ($(PLATFORM),LINUX)
MINILIBX := -L.mlx_linux -lmlx_Linux -lXext -lX11 -lm  
endif

ifeq ($(PLATFORM),MACOS)
MINILIBX := libmlx.dylib
endif

all: $(NAME)

$(NAME):$(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MINILIBX) -o $(NAME)
clean:
	rm -f $(OBJS) get_next_line.o
fclean:clean
	rm -f $(NAME)
re:fclean all
.PHONY: all clean fclean re