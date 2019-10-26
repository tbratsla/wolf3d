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
	wolf->posX = 6;
	wolf->posY = 2;  //x and y start position
	wolf->dirX = -1;
	wolf->dirY = 0; //initial direction vector
	wolf->planeX = 0;
	wolf->planeY = 0.33; //the 2d raycaster version of camera plane
	wolf->time = 0; //time of current frame
	wolf->oldTime = 0; //time of previous frame
	wolf->win = SDL_CreateWindow("Create Level", 0, 0, WIDTH,\
		HEIGHT, SDL_WINDOW_SHOWN);
	wolf->sur = SDL_GetWindowSurface(wolf->win);
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
	wolf->cameraX = 2 * x / WIDTH - 1;
	wolf->rayDirX = wolf->dirX + wolf->planeX * wolf->cameraX;
	wolf->rayDirY = wolf->dirY + wolf->planeY * wolf->cameraX;
	wolf->mapX = (int)wolf->posX;
	wolf->mapY = (int)wolf->posY;
	wolf->deltaDistX = fabs(1 / wolf->rayDirX);
	wolf->deltaDistY = fabs(1 / wolf->rayDirY);
	wolf->hit = 0;
}