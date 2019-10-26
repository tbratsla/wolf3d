/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbratsla <tbratsla@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 12:49:46 by tbratsla          #+#    #+#             */
/*   Updated: 2019/10/09 12:49:47 by tbratsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/wolf3d.h"

void	event(t_wolf *wolf)
{
	if ((wolf->event.key.type == SDL_KEYDOWN &&
  		wolf->event.key.keysym.sym == SDLK_ESCAPE)
  		|| wolf->event.type == SDL_QUIT)
  		exit(1);
  	if (wolf->event.key.type == SDL_KEYDOWN &&
  		(wolf->event.key.keysym.sym == SDLK_w || wolf->event.key.keysym.sym == SDLK_UP))
	{
		ft_clear_screen(wolf);
		if(!wolf->map[(int)(wolf->posX + wolf->dirX * wolf->move_speed)][(int)(wolf->posY)])
			wolf->posX += wolf->dirX * wolf->move_speed;
		if(!wolf->map[(int)(wolf->posX)][(int)(wolf->posY + wolf->dirY * wolf->move_speed)])
			wolf->posY += wolf->dirY * wolf->move_speed;
	}
  	if (wolf->event.key.type == SDL_KEYDOWN &&
  		(wolf->event.key.keysym.sym == SDLK_s || wolf->event.key.keysym.sym == SDLK_DOWN))
	{
		ft_clear_screen(wolf);
		if(!wolf->map[(int)(wolf->posX - wolf->dirX * wolf->move_speed)][(int)(wolf->posY)])
			wolf->posX -= wolf->dirX * wolf->move_speed;
		if(!wolf->map[(int)(wolf->posX)][(int)(wolf->posY - wolf->dirY * wolf->move_speed)])
			wolf->posY -= wolf->dirY * wolf->move_speed;
	}
	if (wolf->event.key.type == SDL_KEYDOWN &&
		wolf->event.key.keysym.sym == SDLK_RIGHT)
		rotation(wolf, 1);
	if (wolf->event.key.type == SDL_KEYDOWN &&
		wolf->event.key.keysym.sym == SDLK_LEFT)
		rotation(wolf, -1);
}

void	rotation(t_wolf *wolf, int side)
{
	double old_dir_x;
	double old_plane_x;

	ft_clear_screen(wolf);
	old_dir_x = wolf->dirX;
	wolf->dirX = wolf->dirX * cos(-wolf->rot_speed * side) - wolf->dirY * sin(-wolf->rot_speed * side);
	wolf->dirY = old_dir_x * sin(-wolf->rot_speed * side) + wolf->dirY * cos(-wolf->rot_speed * side);
	old_plane_x = wolf->planeX;
	wolf->planeX = wolf->planeX * cos(-wolf->rot_speed * side) - wolf->planeY * sin(-wolf->rot_speed * side);
	wolf->planeY = old_plane_x * sin(-wolf->rot_speed * side) + wolf->planeY * cos(-wolf->rot_speed * side);
}