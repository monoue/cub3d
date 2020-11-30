NAME = cub3D
CC = gcc

SRCS =
OBJS =		$(SRCS:%.c=%.o)
CLIBS =		-L . -lft
CFLAGS =	-Wall -Wextra -Werror

SRCS += src/error_exit/error_exit.c

SRCS += src/game_loop/event_hook.c
SRCS += src/game_loop/game_loop.c
SRCS += src/game_loop/map_has_target_at.c
SRCS += src/game_loop/move_player.c
SRCS += src/game_loop/update_and_sort_sprites_data.c
SRCS += src/game_loop/update_sprite_data_utils1.c
SRCS += src/game_loop/update_sprite_data_utils2.c

SRCS += src/game_loop/ray/cast_all_rays_to_wall.c
SRCS += src/game_loop/ray/cast_ray_to_wall_utils.c
SRCS += src/game_loop/ray/coord.c
SRCS += src/game_loop/ray/is_ray_facing.c
SRCS += src/game_loop/ray/seek_hit_utils.c
SRCS += src/game_loop/ray/seek_horizontal_hit.c
SRCS += src/game_loop/ray/seek_vertical_hit.c

SRCS += src/game_loop/render/draw_pixel.c
SRCS += src/game_loop/render/draw_shape.c
SRCS += src/game_loop/render/render_background.c
SRCS += src/game_loop/render/render_mini_map.c
SRCS += src/game_loop/render/render_sprites.c
SRCS += src/game_loop/render/render_wall_ray_basis.c
SRCS += src/game_loop/render/set_texture_color.c

SRCS += src/global/init_g_color.c
SRCS += src/global/init_g_cubfile_data.c
SRCS += src/global/init_g_distance_proj_plane.c
SRCS += src/global/init_g_ids.c
SRCS += src/global/init_g_img.c
SRCS += src/global/init_g_mlx.c
SRCS += src/global/init_g_map.c
SRCS += src/global/init_g_map_to_check.c
SRCS += src/global/init_g_player.c
SRCS += src/global/init_g_rays.c
SRCS += src/global/init_g_save_flag.c
SRCS += src/global/init_g_sprites.c
SRCS += src/global/init_g_textures.c

SRCS += src/main.c

SRCS += src/save_image/save_image.c
SRCS += src/save_image/write_image.c

SRCS += src/set_cubfile_data/create_maps.c
SRCS += src/set_cubfile_data/exit_if_map_is_not_surrounded_by_walls.c
SRCS += src/set_cubfile_data/get_line_data_utils.c
SRCS += src/set_cubfile_data/is_map_line.c
SRCS += src/set_cubfile_data/set_color.c
SRCS += src/set_cubfile_data/set_cubfile_data.c
SRCS += src/set_cubfile_data/set_player_spawning_data.c
SRCS += src/set_cubfile_data/set_texture.c
SRCS += src/set_cubfile_data/set_sprite_position.c

SRCS += src/utils/create_trgb.c
SRCS += src/utils/normalize_angle.c

$(NAME): $(OBJS)
	gcc -g -fsanitize=address $(SRCS) ./libft.a ./libmlx.dylib -o cub3D;
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
