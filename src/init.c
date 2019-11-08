/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbratsla <tbratsla@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 12:51:41 by tbratsla          #+#    #+#             */
/*   Updated: 2019/10/09 12:51:41 by tbratsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/wolf3d.h"

void	init_var(t_wolf *wolf)
{
	wolf->posX = 1.5;
	wolf->posY = 1.5;
	wolf->dirX = -1;
	wolf->dirY = 0;
	wolf->planeX = 0;
	wolf->planeY = 0.33;
	wolf->move_speed = 0.1;
	wolf->rot_speed = 0.02;
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		ft_putendl("ERROR0");
		exit(1);
	}
	wolf->win = SDL_CreateWindow("Create Level", SDL_WINDOWPOS_CENTERED, \
		SDL_WINDOWPOS_CENTERED, WIDTH,\
		HEIGHT, SDL_WINDOW_RESIZABLE);
	wolf->texture = ft_memalloc(sizeof(t_text));
	// if (!(wolf->rend = SDL_CreateRenderer(wolf->win, -1, \
	// 	SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)))
	// {
	// 	ft_putendl("ERROR1");
	// 	exit(1);
	// }
	// if (!(wolf->tex = SDL_CreateTexture(wolf->rend, SDL_PIXELFORMAT_ARGB8888, \
	// 	SDL_TEXTUREACCESS_TARGET, WIDTH, HEIGHT)))
	// {
	// 	ft_putendl("ERROR2");
	// 	exit(1);
	// }
	// wolf->sur = SDL_CreateRGBSurface(0, WIDTH, HEIGHT, 32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);
	
	wolf->sur = SDL_GetWindowSurface(wolf->win);
	load_textures(wolf);
	wolf->events = ft_memalloc(sizeof(t_ev));
	wolf->events->up = 0;
	wolf->events->down = 0;
	wolf->events->r_rot = 0;
	wolf->events->r_move = 0;
	wolf->events->l_move = 0;
	// wolf->angle = 0.0;
	wolf->events->l_rot = 0;
}

void	init_sidedist(t_wolf *wolf)
{
	if (wolf->rayDirX < 0)
	{
		wolf->stepX = -1;
		wolf->sideDistX = (wolf->posX - wolf->mapX) * wolf->deltaDistX;
	}
	else
	{
		wolf->stepX = 1;
		wolf->sideDistX = (wolf->mapX + 1.0 - wolf->posX) * wolf->deltaDistX;
	}
	if (wolf->rayDirY < 0)
	{
		wolf->stepY = -1;
		wolf->sideDistY = (wolf->posY - wolf->mapY) * wolf->deltaDistY;
	}
	else
	{
		wolf->stepY = 1;
		wolf->sideDistY = (wolf->mapY + 1.0 - wolf->posY) * wolf->deltaDistY;
	}
}

void	init_raycast(t_wolf *wolf, int x)
{
	wolf->cameraX = 2 * x / (double)WIDTH - 1;
	wolf->rayDirX = wolf->dirX + wolf->planeX * wolf->cameraX;
	wolf->rayDirY = wolf->dirY + wolf->planeY * wolf->cameraX;
	wolf->mapX = (int)wolf->posX;
	wolf->mapY = (int)wolf->posY;
	wolf->deltaDistX = fabs(1 / wolf->rayDirX);
	wolf->deltaDistY = fabs(1 / wolf->rayDirY);
	wolf->hit = 0;
}
