# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: monoue <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/30 15:33:41 by monoue            #+#    #+#              #
#    Updated: 2020/11/30 16:55:23 by monoue           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
CC = gcc

# PATH
ERROR_EXIT_PATH =	error_exit/
SRCS_PATH =			src/
OBJS_PATH =			obj/
LIBFT_PATH =		$(SRCS_PATH)libft/
GAME_LOOP_PATH =	game_loop/
RAY_PATH =			$(GAME_LOOP_PATH)ray/
RENDER_PATH =		$(GAME_LOOP_PATH)render/
GLOBAL_PATH =		global/
SAVE_IMAGE_PATH =	save_image/
CONFIG_PATH =		config/
UTILS_PATH =		utils/
MINILIBX_PATH = 	minilibx/

SRCS_NAME =
CFLAGS = -Wall -Wextra -Werror

SRCS_NAME += $(ERROR_EXIT_PATH)error_exit.c

SRCS_NAME += $(GAME_LOOP_PATH)event_hook.c
SRCS_NAME += $(GAME_LOOP_PATH)game_loop.c
SRCS_NAME += $(GAME_LOOP_PATH)map_has_target_at.c
SRCS_NAME += $(GAME_LOOP_PATH)move_player.c
SRCS_NAME += $(GAME_LOOP_PATH)update_and_sort_sprites_data.c
SRCS_NAME += $(GAME_LOOP_PATH)update_sprite_data_utils1.c
SRCS_NAME += $(GAME_LOOP_PATH)update_sprite_data_utils2.c

SRCS_NAME += $(RAY_PATH)cast_all_rays_to_wall.c
SRCS_NAME += $(RAY_PATH)cast_ray_to_wall_utils.c
SRCS_NAME += $(RAY_PATH)coord.c
SRCS_NAME += $(RAY_PATH)is_ray_facing.c
SRCS_NAME += $(RAY_PATH)seek_hit_utils.c
SRCS_NAME += $(RAY_PATH)seek_horizontal_hit.c
SRCS_NAME += $(RAY_PATH)seek_vertical_hit.c

SRCS_NAME += $(RENDER_PATH)draw_pixel.c
SRCS_NAME += $(RENDER_PATH)draw_shape.c
SRCS_NAME += $(RENDER_PATH)render_background.c
SRCS_NAME += $(RENDER_PATH)render_mini_map.c
SRCS_NAME += $(RENDER_PATH)render_sprites.c
SRCS_NAME += $(RENDER_PATH)render_wall_ray_basis.c
SRCS_NAME += $(RENDER_PATH)set_texture_color.c

SRCS_NAME += $(GLOBAL_PATH)init_g_color.c
SRCS_NAME += $(GLOBAL_PATH)init_g_config.c
SRCS_NAME += $(GLOBAL_PATH)init_g_distance_proj_plane.c
SRCS_NAME += $(GLOBAL_PATH)init_g_ids.c
SRCS_NAME += $(GLOBAL_PATH)init_g_img.c
SRCS_NAME += $(GLOBAL_PATH)init_g_mlx.c
SRCS_NAME += $(GLOBAL_PATH)init_g_map.c
SRCS_NAME += $(GLOBAL_PATH)init_g_map_to_check.c
SRCS_NAME += $(GLOBAL_PATH)init_g_player.c
SRCS_NAME += $(GLOBAL_PATH)init_g_rays.c
SRCS_NAME += $(GLOBAL_PATH)init_g_save_flag.c
SRCS_NAME += $(GLOBAL_PATH)init_g_sprites.c
SRCS_NAME += $(GLOBAL_PATH)init_g_textures.c

SRCS_NAME += main.c

SRCS_NAME += $(SAVE_IMAGE_PATH)save_image.c
SRCS_NAME += $(SAVE_IMAGE_PATH)write_image.c

SRCS_NAME += $(CONFIG_PATH)create_maps.c
SRCS_NAME += $(CONFIG_PATH)exit_if_map_is_not_surrounded_by_walls.c
SRCS_NAME += $(CONFIG_PATH)get_line_data_utils.c
SRCS_NAME += $(CONFIG_PATH)is_map_line.c
SRCS_NAME += $(CONFIG_PATH)set_color.c
SRCS_NAME += $(CONFIG_PATH)set_config.c
SRCS_NAME += $(CONFIG_PATH)set_player_spawning_data.c
SRCS_NAME += $(CONFIG_PATH)set_texture.c
SRCS_NAME += $(CONFIG_PATH)set_sprite_position.c

SRCS_NAME += $(UTILS_PATH)create_trgb.c
SRCS_NAME += $(UTILS_PATH)normalize_angle.c

SRCS = $(addprefix $(SRCS_PATH), $(SRCS_NAME))
OBJS = $(SRCS:%.c=%.o)

$(NAME): $(OBJS)
	make -C $(LIBFT_PATH)
	make -C $(MINILIBX_PATH)
	gcc -g -fsanitize=address $(OBJS) $(MINILIBX_PATH)libmlx.dylib $(LIBFT_PATH)libft.a -o $(NAME)
	
all: $(NAME)

clean:
	make -C $(LIBFT_PATH)/ clean
	make -C $(MINILIBX_PATH)/ clean
	rm -f $(OBJS)

fclean: clean
	make -C $(LIBFT_PATH)/ fclean
	make -C $(MINILIBX_PATH)/ fclean
	rm -f $(NAME)

re: fclean all

run:
	./cub3D test_map/1.cub

.PHONY: all clean fclean re run
