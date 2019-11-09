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
	// wolf->move_speed = wolf->time * 5.0;
	// wolf->rot_speed = wolf->time * 3.0;
	if (wolf->event.key.type == SDL_KEYDOWN || wolf->event.key.type == SDL_KEYUP)
	{
		if ((wolf->event.key.type == SDL_KEYDOWN &&
			wolf->event.key.keysym.sym == SDLK_ESCAPE)
			|| wolf->event.type == SDL_QUIT)
			exit(1);
		if ((wolf->event.key.keysym.sym == SDLK_w ||\
			wolf->event.key.keysym.sym == SDLK_UP))
			wolf->events->up = wolf->event.key.type == SDL_KEYDOWN;
		if ((wolf->event.key.keysym.sym == SDLK_s ||\
			wolf->event.key.keysym.sym == SDLK_DOWN))
			wolf->events->down = wolf->event.key.type == SDL_KEYDOWN;
		if (wolf->event.key.keysym.sym == SDLK_RIGHT)
			wolf->events->r_rot = wolf->event.key.type == SDL_KEYDOWN;
		if (wolf->event.key.keysym.sym == SDLK_LEFT)
			wolf->events->l_rot = wolf->event.key.type == SDL_KEYDOWN;
		if (wolf->event.key.keysym.sym == SDLK_d)
			wolf->events->r_move = wolf->event.key.type == SDL_KEYDOWN;
		if (wolf->event.key.keysym.sym == SDLK_a)
			wolf->events->l_move = wolf->event.key.type == SDL_KEYDOWN;
		if (wolf->events->up)
			movement(wolf, 1.0);
		if (wolf->events->down)
			movement(wolf, -1.0);
		if (wolf->events->r_rot)
			rotation(wolf, 1, wolf->rot_speed);
		if (wolf->events->l_rot)
			rotation(wolf, -1, wolf->rot_speed);
		if (wolf->events->r_move)
			side_step(wolf, 1);
		if (wolf->events->l_move)
			side_step(wolf, -1);
	}
}

void	side_step(t_wolf *wolf, int side)
{
	ft_clear_screen(wolf);
	rotation(wolf, side, M_PI / 2);
	movement(wolf, 0.2);
	rotation(wolf, -side, M_PI / 2);

}

void	movement(t_wolf *wolf, double side)
{
	ft_clear_screen(wolf);
	if (!wolf->map[(int)(wolf->posX + side * wolf->dirX * wolf->move_speed + 0.2)]\
		[(int)(wolf->posY)] && !wolf->map[(int)(wolf->posX + side * wolf->dirX * wolf->move_speed - 0.2)]\
		[(int)(wolf->posY)])
		wolf->posX += wolf->dirX * wolf->move_speed * side * wolf->time;
	if (!wolf->map[(int)(wolf->posX)][(int)(wolf->posY + side * wolf->dirY\
		* wolf->move_speed + 0.2)]&& !wolf->map[(int)(wolf->posX)][(int)(wolf->posY + side * wolf->dirY\
		* wolf->move_speed - 0.2)])
		wolf->posY += wolf->dirY * wolf->move_speed * side * wolf->time;
}

void	rotation(t_wolf *wolf, int side, double angle)
{
	double old_dir_x;
	double old_plane_x;

	ft_clear_screen(wolf);
	old_dir_x = wolf->dirX;
	wolf->dirX = wolf->dirX * cos(-angle * side) - wolf->dirY\
		* sin(-angle * side);
	wolf->dirY = old_dir_x * sin(-angle * side) + wolf->dirY\
		* cos(-angle * side);
	old_plane_x = wolf->planeX;
	wolf->planeX = wolf->planeX * cos(-angle * side) - wolf->planeY\
		* sin(-angle * side);
	wolf->planeY = old_plane_x * sin(-angle * side) + wolf->planeY\
		* cos(-angle * side);
}
