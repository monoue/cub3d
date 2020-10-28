NAME = cub3D
CC = gcc

SRCS =
OBJS =		$(SRCS:%.c=%.o)
CLIBS =		-L . -lft
CFLAGS =	-Wall -Wextra -Werror

SRCS += src/main.c
SRCS += src/error.c
SRCS += src/player.c

$(NAME): $(OBJS)
	gcc -g -fsanitize=address $(SRCS) ./libft.a -o cub3D;
	# gcc -g -fsanitize=address $(SRCS) ./libft.a ./libmlx.dylib -o cub3D;
	# ar rcs $(NAME) $(OBJS)

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

run:
	./cub3D test_map/1.cub

.PHONY: all clean fclean re run

