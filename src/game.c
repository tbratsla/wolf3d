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

void	draw_fps(t_wolf *wolf)
{
	SDL_Color	color;
	SDL_Surface	*message;
	SDL_Rect	f;
	char		*fps;

	fps = ft_itoa(123);
	f.x = 100;
	f.y = 100;
	color = (SDL_Color){10, 10, 10, 0};
	message = TTF_RenderText_Solid(wolf->font, fps, color);
	SDL_BlitSurface(message, NULL, wolf->sur, &f);
	SDL_UpdateWindowSurface(wolf->win);
	SDL_FreeSurface(message);
	free(fps);
}

void	draw_plus(t_wolf *wolf)
{
	int x;
	int y;

	x = WIDTH / 2 - 10;
	y = HEIGHT / 2;
	wolf->color = 0x2cbf53;
	while (x <  WIDTH / 2 + 10)
	{
		ft_set_pixel(wolf, x, y);
		x++;
	}
	x = WIDTH / 2;
	y = HEIGHT / 2 - 10;
	while (y <  HEIGHT / 2 + 10)
	{
		ft_set_pixel(wolf, x, y);
		y++;
	}
}

void	draw_floor(t_wolf *wolf, int x)
{
	int y;

	if (wolf->drawEnd < 0)
		wolf->drawEnd = HEIGHT;
	y = wolf->drawEnd + 1;
	while (y < HEIGHT)
	{
		wolf->floor.currentDist = HEIGHT / (2.0 * y - HEIGHT);
		wolf->floor.weight = (wolf->floor.currentDist - wolf->floor.distPlayer)\
		/ (wolf->floor.distWall - wolf->floor.distPlayer);
		wolf->floor.curFloorX =  wolf->floor.weight * wolf->floor.floorX_wall +\
		(1.0 - wolf->floor.weight) * wolf->posX;
		wolf->floor.curFloorY = wolf->floor.weight * wolf->floor.floorY_wall\
		+ (1.0 - wolf->floor.weight) * wolf->posY;
		wolf->floor.floorTexX = (int)(wolf->floor.curFloorX * 64) % 64;
		wolf->floor.floorTexY = (int)(wolf->floor.curFloorY * 64) % 64;
		wolf->color = get_pix_from_text(wolf->texture->floor_text[0], wolf->floor.floorTexX, wolf->floor.floorTexY);
		ft_set_pixel(wolf, x, y);
		wolf->color = get_pix_from_text(wolf->texture->floor_text[1], wolf->floor.floorTexX, wolf->floor.floorTexY);
		ft_set_pixel(wolf, x, HEIGHT - y);
		y++;
	}
}

void	calc_floor(t_wolf *wolf, int x)
{
	if (wolf->side == 2)
	{
		wolf->floor.floorX_wall = wolf->mapX;
		wolf->floor.floorY_wall = wolf->mapY + wolf->texture->wall_x;
	}
	if (wolf->side == 0)
	{
		wolf->floor.floorX_wall = wolf->mapX + 1.0;
		wolf->floor.floorY_wall = wolf->mapY + wolf->texture->wall_x;
	}
	if (wolf->side == 3)
	{
		wolf->floor.floorX_wall = wolf->mapX + wolf->texture->wall_x;
		wolf->floor.floorY_wall = wolf->mapY;
	}
	if (wolf->side == 1)
	{
		wolf->floor.floorX_wall = wolf->mapX + wolf->texture->wall_x;
		wolf->floor.floorY_wall = wolf->mapY + 1.0;
	}
	wolf->floor.distWall = wolf->perpWallDist;
	wolf->floor.distPlayer = 0.0;
	draw_floor(wolf, x);
}

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
	int				x;
	unsigned int	ticks;

	init_var(wolf);
	ticks = 10;
	SDL_SetRelativeMouseMode(SDL_TRUE);
	while (1)
	{
		ticks = SDL_GetTicks();
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
			if (wolf->text_flag == 1)
			{
				calc_wall(wolf, x);
				calc_floor(wolf, x);
			}
			if (wolf->text_flag == 0)
			{
				set_color(wolf);
				draw_vert_line(wolf, x);
			}
			draw_plus(wolf);
			x++;
		}
		draw_fps(wolf);
		wolf->time = (SDL_GetTicks() - ticks) / 10;
		while (wolf->time < 2)
			wolf->time = (SDL_GetTicks() - ticks) / 10;
	}
}
