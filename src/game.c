/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbratsla <tbratsla@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 14:10:23 by tbratsla          #+#    #+#             */
/*   Updated: 2019/10/07 14:10:24 by tbratsla         ###   ########.fr       */
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
	if (wolf->side == 1)
      	wolf->color = wolf->color / 2;
}

void	ft_set_pixel(t_wolf *wolf, int x, int y)
{
	int  *pic;

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

void	calc_height(t_wolf *wolf)
{
	wolf->lineHeight = (int)(HEIGHT / wolf->perpWallDist);
	wolf->drawStart = -wolf->lineHeight / 2 + HEIGHT / 2;
	if(wolf->drawStart < 0)
		wolf->drawStart = 0;
	wolf->drawEnd = wolf->lineHeight / 2 + HEIGHT / 2;
	if(wolf->drawEnd >= HEIGHT)
		wolf->drawEnd = HEIGHT - 1;
}

void	search_wall(t_wolf *wolf)
{
	while (wolf->hit == 0)
	{
		if (wolf->sideDistX < wolf->sideDistY)
		{
			wolf->sideDistX += wolf->deltaDistX;
			wolf->mapX += wolf->stepX;
			wolf->side = 0;
		}
		else
		{
			wolf->sideDistY += wolf->deltaDistY;
			wolf->mapY += wolf->stepY;
			wolf->side = 1;
		}
		if (wolf->map[wolf->mapX] && wolf->map[wolf->mapX][wolf->mapY]
			&& wolf->map[wolf->mapX][wolf->mapY] > 0)
			wolf->hit = 1;
	}
	if (wolf->side == 0)
      	wolf->perpWallDist = (wolf->mapX - wolf->posX + (1 - wolf->stepX)\
      		/ 2) / wolf->rayDirX;
	else
		wolf->perpWallDist = (wolf->mapY - wolf->posY + (1 - wolf->stepY)\
			/ 2) / wolf->rayDirY;
}

void	game(t_wolf *wolf)
{
	int		x;

	init_var(wolf);
	while (1)
	{
		while (SDL_PollEvent(&wolf->event))
   			event(wolf);
   		x = 0;
   		while (x < WIDTH)
   		{
   			init_raycast(wolf, x);
   			init_sidedist(wolf);
      		search_wall(wolf);
      		calc_height(wolf);
      		set_color(wolf);
      		draw_vert_line(wolf, x);
   			x++;
   		}
		SDL_UpdateWindowSurface(wolf->win);
	}
}