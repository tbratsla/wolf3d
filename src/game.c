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

void	comp_main_cycle(t_wolf *wolf, int *x)
{
	init_raycast(wolf, *x);
	init_sidedist(wolf);
	search_wall(wolf);
	calc_height(wolf);
	if (wolf->text_flag == 1)
	{
		calc_wall(wolf, *x);
		calc_floor(wolf, *x);
	}
	if (wolf->text_flag == 0)
	{
		set_color(wolf);
		draw_vert_line(wolf, *x);
	}
	draw_plus(wolf);
	(*x)++;
}

void	search_wall(t_wolf *wolf)
{
	while (wolf->hit == 0)
	{
		if (wolf->side_dist_x < wolf->side_dist_y)
		{
			wolf->side_dist_x += wolf->delta_dist_x;
			wolf->map_x += wolf->step_x;
			wolf->side = 0;
			if (wolf->raydir_x > 0)
				wolf->side = 2;
		}
		else
		{
			wolf->side_dist_y += wolf->delta_dist_y;
			wolf->map_y += wolf->step_y;
			wolf->side = 1;
			if (wolf->raydir_y > 0)
				wolf->side = 3;
		}
		if (wolf->map[wolf->map_x] && wolf->map[wolf->map_x][wolf->map_y]
			&& wolf->map[wolf->map_x][wolf->map_y] > 0)
			wolf->hit = 1;
	}
}

void	game(t_wolf *wolf)
{
	int				x;
	unsigned int	ticks;

	init_var(wolf);
	ticks = 0;
	SDL_SetRelativeMouseMode(SDL_TRUE);
	while (1)
	{
		ticks = SDL_GetTicks();
		while (SDL_PollEvent(&wolf->event))
			event(wolf);
		SDL_GetRelativeMouseState(&wolf->mouse.x, &wolf->mouse.y);
		rotation(wolf, 1, wolf->mouse.x * wolf->rot_speed / 10);
		x = 0;
		while (x < WIDTH)
			comp_main_cycle(wolf, &x);
		wolf->time = (SDL_GetTicks() - ticks) / 10.0;
		draw_fps(wolf);
		while (wolf->time < 2)
			wolf->time = (SDL_GetTicks() - ticks) / 10.0;
	}
}
