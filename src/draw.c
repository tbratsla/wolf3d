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

void	set_color(t_wolf *wolf)
{
	if (wolf->map[wolf->mapX][wolf->mapY] == 1)
		wolf->color = GREEN;
	if (wolf->map[wolf->mapX][wolf->mapY] == 2)
		wolf->color = BLUE;
	if (wolf->map[wolf->mapX][wolf->mapY] == 3)
		wolf->color = RED;
	if (wolf->map[wolf->mapX][wolf->mapY] == 4)
		wolf->color = YELLOW;
	if (wolf->map[wolf->mapX][wolf->mapY] == 5)
		wolf->color = ARGENT;
	if (wolf->map[wolf->mapX][wolf->mapY] == 6)
		wolf->color = PURPURE;
	if (wolf->side == 1)
		wolf->color = wolf->color / 2;
	if (wolf->side == 2)
		wolf->color = wolf->color * 2;
	if (wolf->side == 3)
		wolf->color = wolf->color * 3;
}

void	ft_set_pixel(t_wolf *wolf, int x, int y)
{
	int		*pic;

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
