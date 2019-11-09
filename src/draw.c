/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbratsla <tbratsla@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 13:42:11 by tbratsla          #+#    #+#             */
/*   Updated: 2019/10/26 13:42:11 by tbratsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/wolf3d.h"

Uint32	get_pix_from_text(SDL_Surface *text, int x, int y)
{
	Uint32	*tmp;

	x %= 64;
	y %= 64;
	if (!text)
		return (0x000000);
	if (!text->pixels)
		return (0x000000);
	if (!text->w)
		return (0x000000);
	if (text->w != 64)
		return (0x000000);
	tmp = (Uint32 *)text->pixels;
	return (tmp[(y * text->w) + x]);
}

void	set_color(t_wolf *wolf)
{
	if (wolf->map[wolf->mapX][wolf->mapY] % 9 == 1)
		wolf->color = GREEN;
	if (wolf->map[wolf->mapX][wolf->mapY] % 9 == 2)
		wolf->color = BLUE;
	if (wolf->map[wolf->mapX][wolf->mapY] % 9 == 3)
		wolf->color = RED;
	if (wolf->map[wolf->mapX][wolf->mapY] % 9== 4)
		wolf->color = YELLOW;
	if (wolf->map[wolf->mapX][wolf->mapY] % 9 == 5)
		wolf->color = ARGENT;
	if (wolf->map[wolf->mapX][wolf->mapY] % 9 == 6)
		wolf->color = PURPURE;
	if (wolf->map[wolf->mapX][wolf->mapY] % 9 == 7)
		wolf->color = RED;
	if (wolf->map[wolf->mapX][wolf->mapY] % 9 == 8)
		wolf->color = RED;
	if (wolf->side == 1)
		wolf->color = wolf->color / 2;
	if (wolf->side == 2)
		wolf->color = wolf->color * 2;
	if (wolf->side == 3)
		wolf->color = wolf->color * 3;
	// SDL_SetRenderDrawColor(wolf->rend, (wolf->color >> 16) % 256, \
	// 	(wolf->color >> 8) % 256 , wolf->color % 256, 128);
}

void	ft_set_pixel(t_wolf *wolf, int x, int y)
{
	Uint32	*pic;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT && wolf->color)
	{
		pic = wolf->sur->pixels + y * wolf->sur->pitch +
		x * wolf->sur->format->BytesPerPixel;
		*pic = wolf->color;
	}
}

void	draw_vert_line(t_wolf *wolf, int x)
{
	int		y;

	y = wolf->drawStart;
	while (y < wolf->drawEnd)
	{
		// SDL_RenderDrawPoint(wolf->rend, x, y);
		ft_set_pixel(wolf, x, y);
		y++;
	}
}

void	ft_clear_screen(t_wolf *wolf)
{
	int		x;
	int		*pic;
	int		y;

	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			pic = wolf->sur->pixels + y * wolf->sur->pitch +
			x * wolf->sur->format->BytesPerPixel;
			*pic = 0x000000;
			y++;
		}
		x++;
	}
}
