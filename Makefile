# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: monoue <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/30 15:33:41 by monoue            #+#    #+#              #
#    Updated: 2020/12/09 16:59:24 by monoue           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
CC = gcc

# PATH
ERROR_EXIT_PATH =	error_exit/
SRCS_PATH =			src/
BONUS_PATH =		bonus/
LIBFT_PATH =		libft/
GAME_LOOP_PATH =	game_loop/
RAY_PATH =			$(GAME_LOOP_PATH)ray/
RENDER_PATH =		$(GAME_LOOP_PATH)render/
GLOBAL_PATH =		global/
SAVE_IMAGE_PATH =	save_image/
CONFIG_PATH =		set_config/
UTILS_PATH =		utils/
MINILIBX_PATH = 	minilibx/

LIBFT =				$(LIBFT_PATH)libft.a
MINILIBX =			$(MINILIBX_PATH)libmlx.dylib

SRCS_NAME =
BONUS_NAME =

CFLAGS = -Wall -Wextra -Werror

SRCS_NAME += $(ERROR_EXIT_PATH)error_exit.c
SRCS_NAME += $(ERROR_EXIT_PATH)exit_if_closing_fd_error.c
SRCS_NAME += $(ERROR_EXIT_PATH)map_error.c

SRCS_NAME += $(GAME_LOOP_PATH)event_hook.c
SRCS_NAME += $(GAME_LOOP_PATH)game_loop.c
SRCS_NAME += $(GAME_LOOP_PATH)map_has_target_at.c
SRCS_NAME += $(GAME_LOOP_PATH)move_player.c
SRCS_NAME += $(GAME_LOOP_PATH)update_and_sort_sprites_data.c
SRCS_NAME += $(GAME_LOOP_PATH)update_sprite_data_utils1.c
SRCS_NAME += $(GAME_LOOP_PATH)update_sprite_data_utils2.c
SRCS_NAME += $(GAME_LOOP_PATH)sort_sprites.c

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
SRCS_NAME += $(GLOBAL_PATH)init_g_map.c
SRCS_NAME += $(GLOBAL_PATH)init_g_map_to_check.c
SRCS_NAME += $(GLOBAL_PATH)init_g_minimap_flag.c
SRCS_NAME += $(GLOBAL_PATH)init_g_mlx.c
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
SRCS_NAME += $(CONFIG_PATH)free_str_array.c
SRCS_NAME += $(CONFIG_PATH)get_line_data_utils.c
SRCS_NAME += $(CONFIG_PATH)is_map_line.c
SRCS_NAME += $(CONFIG_PATH)malloc_rays_wall_hit_coord.c
SRCS_NAME += $(CONFIG_PATH)set_color.c
SRCS_NAME += $(CONFIG_PATH)set_config.c
SRCS_NAME += $(CONFIG_PATH)set_player_spawning_data.c
SRCS_NAME += $(CONFIG_PATH)set_texture_if_valid.c
SRCS_NAME += $(CONFIG_PATH)set_sprite_position.c

SRCS_NAME += $(UTILS_PATH)create_trgb.c
SRCS_NAME += $(UTILS_PATH)normalize_angle.c

SRCS = $(addprefix $(SRCS_PATH), $(SRCS_NAME))
OBJS = $(SRCS:%.c=%.o)

BONUS_NAME += $(ERROR_EXIT_PATH)error_exit_bonus.c
BONUS_NAME += $(ERROR_EXIT_PATH)exit_if_closing_fd_error_bonus.c
BONUS_NAME += $(ERROR_EXIT_PATH)map_error_bonus.c

BONUS_NAME += $(GAME_LOOP_PATH)event_hook_bonus.c
BONUS_NAME += $(GAME_LOOP_PATH)game_loop_bonus.c
BONUS_NAME += $(GAME_LOOP_PATH)map_has_target_at_bonus.c
BONUS_NAME += $(GAME_LOOP_PATH)move_player_bonus.c
BONUS_NAME += $(GAME_LOOP_PATH)update_and_sort_sprites_data_bonus.c
BONUS_NAME += $(GAME_LOOP_PATH)update_sprite_data_utils1_bonus.c
BONUS_NAME += $(GAME_LOOP_PATH)update_sprite_data_utils2_bonus.c
BONUS_NAME += $(GAME_LOOP_PATH)sort_sprites_bonus.c

BONUS_NAME += $(RAY_PATH)cast_all_rays_to_wall_bonus.c
BONUS_NAME += $(RAY_PATH)cast_ray_to_wall_utils_bonus.c
BONUS_NAME += $(RAY_PATH)coord_bonus.c
BONUS_NAME += $(RAY_PATH)is_ray_facing_bonus.c
BONUS_NAME += $(RAY_PATH)seek_hit_utils_bonus.c
BONUS_NAME += $(RAY_PATH)seek_horizontal_hit_bonus.c
BONUS_NAME += $(RAY_PATH)seek_vertical_hit_bonus.c

BONUS_NAME += $(RENDER_PATH)draw_pixel_bonus.c
BONUS_NAME += $(RENDER_PATH)draw_shape_bonus.c
BONUS_NAME += $(RENDER_PATH)render_background_bonus.c
BONUS_NAME += $(RENDER_PATH)render_mini_map_bonus.c
BONUS_NAME += $(RENDER_PATH)render_sprites_bonus.c
BONUS_NAME += $(RENDER_PATH)render_wall_ray_basis_bonus.c
BONUS_NAME += $(RENDER_PATH)set_texture_color_bonus.c

BONUS_NAME += $(GLOBAL_PATH)init_g_color_bonus.c
BONUS_NAME += $(GLOBAL_PATH)init_g_config_bonus.c
BONUS_NAME += $(GLOBAL_PATH)init_g_distance_proj_plane_bonus.c
BONUS_NAME += $(GLOBAL_PATH)init_g_ids_bonus.c
BONUS_NAME += $(GLOBAL_PATH)init_g_img_bonus.c
BONUS_NAME += $(GLOBAL_PATH)init_g_map_bonus.c
BONUS_NAME += $(GLOBAL_PATH)init_g_map_to_check_bonus.c
BONUS_NAME += $(GLOBAL_PATH)init_g_minimap_flag_bonus.c
BONUS_NAME += $(GLOBAL_PATH)init_g_mlx_bonus.c
BONUS_NAME += $(GLOBAL_PATH)init_g_player_bonus.c
BONUS_NAME += $(GLOBAL_PATH)init_g_rays_bonus.c
BONUS_NAME += $(GLOBAL_PATH)init_g_save_flag_bonus.c
BONUS_NAME += $(GLOBAL_PATH)init_g_sprites_bonus.c
BONUS_NAME += $(GLOBAL_PATH)init_g_textures_bonus.c

BONUS_NAME += main_bonus.c

BONUS_NAME += $(SAVE_IMAGE_PATH)save_image_bonus.c
BONUS_NAME += $(SAVE_IMAGE_PATH)write_image_bonus.c

BONUS_NAME += $(CONFIG_PATH)create_maps_bonus.c
BONUS_NAME += $(CONFIG_PATH)exit_if_map_is_not_surrounded_by_walls_bonus.c
BONUS_NAME += $(CONFIG_PATH)free_str_array_bonus.c
BONUS_NAME += $(CONFIG_PATH)get_line_data_utils_bonus.c
BONUS_NAME += $(CONFIG_PATH)is_map_line_bonus.c
BONUS_NAME += $(CONFIG_PATH)malloc_rays_wall_hit_coord_bonus.c
BONUS_NAME += $(CONFIG_PATH)set_color_bonus.c
BONUS_NAME += $(CONFIG_PATH)set_config_bonus.c
BONUS_NAME += $(CONFIG_PATH)set_player_spawning_data_bonus.c
BONUS_NAME += $(CONFIG_PATH)set_texture_if_valid_bonus.c
BONUS_NAME += $(CONFIG_PATH)set_sprite_position_bonus.c

BONUS_NAME += $(UTILS_PATH)create_trgb_bonus.c
BONUS_NAME += $(UTILS_PATH)normalize_angle_bonus.c

BSRCS = $(addprefix $(BONUS_PATH), $(BONUS_NAME))
BOBJS = $(BSRCS:%.c=%.o)

$(NAME): $(OBJS)
	$(MAKE) -C $(LIBFT_PATH)
	$(MAKE) -C $(MINILIBX_PATH)
	cp -f $(MINILIBX) .
	$(CC) $^ -L$(LIBFT_PATH) -lft -L. -lmlx -o $@

all: $(NAME)

bonus: $(BOBJS)
	$(MAKE) -C $(LIBFT_PATH)
	$(MAKE) -C $(MINILIBX_PATH)
	cp -f $(MINILIBX) .
	$(CC) $^ -L$(LIBFT_PATH) -lft -L. -lmlx -o $(NAME)

clean:
	$(MAKE) -C $(LIBFT_PATH) clean
	$(MAKE) -C $(MINILIBX_PATH) clean
	find . -name *.o -print0 | xargs -0 $(RM)

fclean: clean
	$(MAKE) -C $(LIBFT_PATH) fclean
	$(MAKE) -C $(MINILIBX_PATH) fclean
	$(RM) $(NAME)
	find . -name *.dylib -print0 | xargs -0 $(RM)

re: fclean all

.PHONY: all clean fclean re run
