/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 10:39:11 by monoue            #+#    #+#             */
/*   Updated: 2020/10/14 08:10:16 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

static SDL_Window	*g_window = NULL;
static SDL_Renderer	*g_renderer = NULL;
static uint32_t		*g_color_buffer = NULL;
static SDL_Texture	*g_color_buffer_texture;

bool	initialize_window(void)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == SDL_ERROR)
	{
		ft_putstr_fd("Error initializing SDL.\n", STDERR_FILENO);
		return (false);
	}
	SDL_DisplayMode display_mode;
	SDL_GetCurrentDisplayMode(0, &display_mode);
	int	fullScreenWidth = display_mode.w;
	int	fullScreenHeight = display_mode.h;
	g_window = SDL_CreateWindow
	(
		NULL,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		fullScreenWidth,
		fullScreenHeight,
		SDL_WINDOW_BORDERLESS
	);
	if (g_window == NULL)
	{
		ft_putstr_fd("Error creating SDL window.\n", STDERR_FILENO);
		return (false);
	}
	g_renderer = SDL_CreateRenderer(g_window, DEFAULT_GRAPHIC_DRIVER, 0);
	if (g_renderer == NULL)
	{
		ft_putstr_fd("Error creating SDL renderer.\n", STDERR_FILENO);
		return (false);
	}
	SDL_SetRenderDrawBlendMode(g_renderer, SDL_BLENDMODE_BLEND);
	g_color_buffer = malloc(sizeof(uint32_t) * (uint32_t)WINDOW_WIDTH * (uint32_t)WINDOW_HEIGHT);
	//	create an SDL Texture to display the colorbuffer
	g_color_buffer_texture = SDL_CreateTexture(
		g_renderer,
		SDL_PIXELFORMAT_RGBA32,
		SDL_TEXTUREACCESS_STREAMING,
		WINDOW_WIDTH,
		WINDOW_HEIGHT
	);
	return (true);
}

void	destroy_window(void)
{
	free(g_color_buffer);
	SDL_DestroyTexture(g_color_buffer_texture);
	SDL_DestroyRenderer(g_renderer);
	SDL_DestroyWindow(g_window);
	SDL_Quit();
}

void	clear_color_buffer(t_color color)
{
	int	index;

	index = 0;
	while (index < WINDOW_WIDTH * WINDOW_HEIGHT)
	{
		g_color_buffer[index] = color;
		index++;
	}
}

void	render_color_buffer(void)
{
	// second parameter -> the rectangle I want to update. This time, entire -> null
	SDL_UpdateTexture
	(
		g_color_buffer_texture,
		NULL,
		g_color_buffer,
		(int)(WINDOW_WIDTH * sizeof(t_color))
	);
	//	from NULL to NULL -> the entire texture
	SDL_RenderCopy(g_renderer, g_color_buffer_texture, NULL, NULL);
	SDL_RenderPresent(g_renderer);
}

void	my_mlx_pixel_put(t_data *img, int x, int y, int color)
{
	char *dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	draw_pixel(int x, int y, t_color color)
{
	g_color_buffer[(WINDOW_WIDTH * y) + x] = color;



	char *dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	draw_rect(int x, int y, int width, int height, t_color color)
{
	int	xi;
	int	yi;

	yi = y;
	while (yi < y + height)
	{
		xi = x;
		while (xi < x + width)
		{
			draw_pixel(xi, yi, color);
			xi++;
		}
		yi++;
	}
}

void	draw_line(int x0, int y0, int x1, int y1, t_color color)
{
	int		delta_x;
	int		delta_y;
	int		longer_side_length;
	int		index;
	float	x_increment;
	float	y_increment;
	float	current_x;
	float	current_y;

	delta_x = (x1 - x0);
	delta_y = (y1 - y0);
	longer_side_length = (abs(delta_x)) >= abs(delta_y) ? abs(delta_x) : abs(delta_y);
	x_increment = delta_x / (float)longer_side_length;
	y_increment = delta_y / (float)longer_side_length;
	current_x = x0;
	current_y = y0;
	index = 0;
	while (index < longer_side_length)
	{
		draw_pixel(round(current_x), round(current_y), color);
		current_x += x_increment;
		current_y += y_increment;
		index++;
	}
}