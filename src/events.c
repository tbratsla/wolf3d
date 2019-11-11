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

void	event2(t_wolf *wolf)
{
	if (wolf->event.key.keysym.sym == SDLK_RETURN &&\
		wolf->event.type != SDL_KEYUP)
		wolf->text_flag = wolf->text_flag ? 0 : 1;
	if (wolf->event.key.keysym.sym == SDLK_LSHIFT ||\
		wolf->event.key.keysym.sym == SDLK_RSHIFT)
		wolf->move_speed = (wolf->move_speed == 0.05) ? 0.07 : 0.05;
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

void	event(t_wolf *wolf)
{
	if ((wolf->event.key.type == SDL_KEYDOWN &&\
			wolf->event.key.keysym.sym == SDLK_ESCAPE)\
			|| wolf->event.type == SDL_QUIT)
		exit(1);
	if (wolf->event.key.type == SDL_KEYDOWN ||\
		wolf->event.key.type == SDL_KEYUP)
	{
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
		event2(wolf);
	}
}

void	side_step(t_wolf *wolf, int side)
{
	double tmp;
	double old_dir_x;
	double old_dir_y;

	old_dir_x = wolf->dir_x;
	old_dir_y = wolf->dir_y;
	tmp = wolf->dir_x;
	old_dir_x = old_dir_x * cos(-M_PI / 2) - old_dir_y\
		* sin(-M_PI / 2);
	old_dir_y = tmp * sin(-M_PI / 2) + old_dir_y\
		* cos(-M_PI / 2);
	if (!wolf->map[(int)(wolf->pos_x + side * old_dir_x *\
		wolf->move_speed * 3)][(int)(wolf->pos_y)])
		wolf->pos_x += old_dir_x * 0.02 * side * wolf->time;
	if (!wolf->map[(int)(wolf->pos_x)][(int)(wolf->pos_y + side * old_dir_y\
		* wolf->move_speed * 3)])
		wolf->pos_y += old_dir_y * 0.02 * side * wolf->time;
}

void	movement(t_wolf *wolf, double side)
{
	ft_clear_screen(wolf);
	if (!wolf->map[(int)(wolf->pos_x + side * wolf->dir_x *\
		wolf->move_speed * 3)][(int)(wolf->pos_y)])
		wolf->pos_x += wolf->dir_x * wolf->move_speed * side * wolf->time;
	if (!wolf->map[(int)(wolf->pos_x)][(int)(wolf->pos_y + side * wolf->dir_y\
		* wolf->move_speed * 3)])
		wolf->pos_y += wolf->dir_y * wolf->move_speed * side * wolf->time;
}

void	rotation(t_wolf *wolf, int side, double angle)
{
	double old_dir_x;
	double old_plane_x;

	ft_clear_screen(wolf);
	old_dir_x = wolf->dir_x;
	wolf->dir_x = wolf->dir_x * cos(-angle * side) - wolf->dir_y\
		* sin(-angle * side);
	wolf->dir_y = old_dir_x * sin(-angle * side) + wolf->dir_y\
		* cos(-angle * side);
	old_plane_x = wolf->plane_x;
	wolf->plane_x = wolf->plane_x * cos(-angle * side) - wolf->plane_y\
		* sin(-angle * side);
	wolf->plane_y = old_plane_x * sin(-angle * side) + wolf->plane_y\
		* cos(-angle * side);
}
