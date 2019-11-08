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

void	calc_wall(t_wolf *wolf, int x)
{
	wolf->texture->text_num = wolf->map[wolf->mapX][wolf->mapY] - 1;
	if (wolf->side == 1)
		wolf->texture->text_num = (wolf->texture->text_num + 1) % TEXTNUM;
	if (wolf->side == 2)
		wolf->texture->text_num = (wolf->texture->text_num + 2) % TEXTNUM;
	if (wolf->side == 3)
		wolf->texture->text_num = (wolf->texture->text_num + 3) % TEXTNUM;
	if (wolf->side == 0 || wolf->side == 2)
		wolf->texture->wall_x = wolf->posY + wolf->perpWallDist * wolf->rayDirY;
	else
		wolf->texture->wall_x = wolf->posX + wolf->perpWallDist * wolf->rayDirX;
	wolf->texture->wall_x -= floor(wolf->texture->wall_x);
	wolf->texture->text_x = (int)(wolf->texture->wall_x * 64.0);
	if (wolf->side == 2 || wolf->side == 1)
		wolf->texture->text_x = 64 - wolf->texture->text_x - 1;
	calc_y(wolf, x);
}

void	calc_y(t_wolf *wolf, int x)
{
	int y;

	y = wolf->drawStart;
	while (y < wolf->drawEnd)
	{
		wolf->texture->magic_d = y * 256 - HEIGHT * 128 + wolf->lineHeight * 128;
		wolf->texture->text_y = ((wolf->texture->magic_d * 64) / wolf->lineHeight) / 256;
		wolf->color = get_pix_from_text(wolf->texture->wall_text[wolf->texture->text_num], wolf->texture->text_x, wolf->texture->text_y);
		ft_set_pixel(wolf, x, y);
		y++;
	}
}

void	calc_height(t_wolf *wolf)
{
	wolf->lineHeight = (int)(HEIGHT / wolf->perpWallDist);
	wolf->drawStart = -wolf->lineHeight / 2 + HEIGHT / 2;
	if (wolf->drawStart < 0)
		wolf->drawStart = 0;
	wolf->drawEnd = wolf->lineHeight / 2 + HEIGHT / 2;
	if (wolf->drawEnd >= HEIGHT)
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
			if (wolf->rayDirX > 0)
				wolf->side = 2;
		}
		else
		{
			wolf->sideDistY += wolf->deltaDistY;
			wolf->mapY += wolf->stepY;
			wolf->side = 1;
			if (wolf->rayDirY > 0)
				wolf->side = 3;
		}
		if (wolf->map[wolf->mapX] && wolf->map[wolf->mapX][wolf->mapY]
			&& wolf->map[wolf->mapX][wolf->mapY] > 0)
			wolf->hit = 1;
	}
	if (wolf->side == 0 || wolf->side == 2)
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
	SDL_SetRelativeMouseMode(SDL_TRUE);
	while (1)
	{
		while (SDL_PollEvent(&wolf->event))
			event(wolf);
		SDL_GetRelativeMouseState(&wolf->mouse.x,&wolf->mouse.y);
 		rotation(wolf, 1, wolf->mouse.x * wolf->rot_speed / 10);
		x = 0;
		while (x < WIDTH)
		{
			init_raycast(wolf, x);
			init_sidedist(wolf);
			search_wall(wolf);
			calc_height(wolf);
			calc_wall(wolf, x);
			x++;
		}
		SDL_UpdateWindowSurface(wolf->win);
	}
}
