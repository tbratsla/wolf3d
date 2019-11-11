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

void	get_player_position(t_wolf *wolf)
{
	int i;
	int j;

	i = 0;
	while (i < wolf->count_str)
	{
		j = 0;
		while (j < wolf->count_num)
		{
			if (!wolf->map[i][j])
			{
				wolf->pos_x = i + 0.5;
				wolf->pos_y = j + 0.5;
				return ;
			}
			j++;
		}
		i++;
	}
	if (!wolf->pos_x || !wolf->pos_y)
	{
		ft_putendl("Error9: No space to spawn player");
		exit(1);
	}
}

void	init_var(t_wolf *wolf)
{
	wolf->pos_x = 0;
	wolf->pos_y = 0;
	check_map_side(wolf);
	get_player_position(wolf);
	wolf->dir_x = -1;
	wolf->dir_y = 0;
	wolf->plane_x = 0;
	wolf->plane_y = 0.33;
	wolf->move_speed = 0.05;
	wolf->rot_speed = 0.02;
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		ft_putendl("Error init SDL");
		exit(1);
	}
	wolf->win = SDL_CreateWindow("Create Level", SDL_WINDOWPOS_CENTERED, \
		SDL_WINDOWPOS_CENTERED, WIDTH,\
		HEIGHT, SDL_WINDOW_RESIZABLE);
	TTF_Init();
	init_var2(wolf);
}

void	init_var2(t_wolf *wolf)
{
	wolf->texture = ft_memalloc(sizeof(t_text));
	wolf->sur = SDL_GetWindowSurface(wolf->win);
	load_textures(wolf);
	wolf->events = ft_memalloc(sizeof(t_ev));
	wolf->events->up = 0;
	wolf->events->down = 0;
	wolf->events->r_rot = 0;
	wolf->events->r_move = 0;
	wolf->events->l_move = 0;
	wolf->events->l_rot = 0;
	wolf->time = 0.1;
	wolf->text_flag = 0;
	wolf->font = TTF_OpenFont("font/font.ttf", 80);
	if (wolf->font == NULL)
	{
		ft_putendl("Error load font.ttf");
		exit(1);
	}
}

void	init_sidedist(t_wolf *wolf)
{
	if (wolf->raydir_x < 0)
	{
		wolf->step_x = -1;
		wolf->side_dist_x = (wolf->pos_x - wolf->map_x) * wolf->delta_dist_x;
	}
	else
	{
		wolf->step_x = 1;
		wolf->side_dist_x = (wolf->map_x + 1.0 -\
			wolf->pos_x) * wolf->delta_dist_x;
	}
	if (wolf->raydir_y < 0)
	{
		wolf->step_y = -1;
		wolf->side_dist_y = (wolf->pos_y - wolf->map_y) * wolf->delta_dist_y;
	}
	else
	{
		wolf->step_y = 1;
		wolf->side_dist_y = (wolf->map_y + 1.0 -\
			wolf->pos_y) * wolf->delta_dist_y;
	}
}

void	init_raycast(t_wolf *wolf, int x)
{
	wolf->camera_x = 2 * x / (double)WIDTH - 1;
	wolf->raydir_x = wolf->dir_x + wolf->plane_x * wolf->camera_x;
	wolf->raydir_y = wolf->dir_y + wolf->plane_y * wolf->camera_x;
	wolf->map_x = (int)wolf->pos_x;
	wolf->map_y = (int)wolf->pos_y;
	wolf->delta_dist_x = fabs(1 / wolf->raydir_x);
	wolf->delta_dist_y = fabs(1 / wolf->raydir_y);
	wolf->hit = 0;
}
