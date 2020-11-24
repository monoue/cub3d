NAME = cub3D
CC = gcc

SRCS =
OBJS =		$(SRCS:%.c=%.o)
CLIBS =		-L . -lft
CFLAGS =	-Wall -Wextra -Werror

SRCS += src/cast_all_rays_to_wall.c
SRCS += src/cast_ray_to_wall_utils.c
SRCS += src/coord.c
SRCS += src/create_maps.c
SRCS += src/draw_shape.c
SRCS += src/error.c
SRCS += src/event_hook.c
SRCS += src/get_line_data_utils.c
SRCS += src/graphics.c
SRCS += src/init_mlx.c
SRCS += src/is_map_line.c
SRCS += src/is_ray_facing.c
SRCS += src/main.c
SRCS += src/map_has_wall_at.c
SRCS += src/map_error.c
SRCS += src/normalize_angle.c
SRCS += src/player.c
SRCS += src/render/render_background.c
SRCS += src/render/render_sprites.c
SRCS += src/render/render_mini_map.c
SRCS += src/render/render_wall_ray_basis.c
SRCS += src/save_image.c
SRCS += src/seek_hit_utils.c
SRCS += src/seek_horizontal_hit.c
SRCS += src/seek_vertical_hit.c
SRCS += src/set_color.c
SRCS += src/set_cubfile_data.c
SRCS += src/write_image.c
SRCS += src/sprite.c

SRCS += src/test.c

$(NAME): $(OBJS)
	gcc -g -fsanitize=address $(SRCS) ./libft.a ./libmlx.dylib -o cub3D;
	# gcc -g -fsanitize=address $(SRCS) ./libft.a -o cub3D;
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
