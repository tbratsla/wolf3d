/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbratsla <tbratsla@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 12:15:04 by tbratsla          #+#    #+#             */
/*   Updated: 2019/11/11 12:15:05 by tbratsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/wolf3d.h"

void	calc_floor(t_wolf *wolf, int x)
{
	if (wolf->side == 2)
	{
		wolf->floor.floor_x_wall = wolf->map_x;
		wolf->floor.floor_y_wall = wolf->map_y + wolf->texture->wall_x;
	}
	if (wolf->side == 0)
	{
		wolf->floor.floor_x_wall = wolf->map_x + 1.0;
		wolf->floor.floor_y_wall = wolf->map_y + wolf->texture->wall_x;
	}
	if (wolf->side == 3)
	{
		wolf->floor.floor_x_wall = wolf->map_x + wolf->texture->wall_x;
		wolf->floor.floor_y_wall = wolf->map_y;
	}
	if (wolf->side == 1)
	{
		wolf->floor.floor_x_wall = wolf->map_x + wolf->texture->wall_x;
		wolf->floor.floor_y_wall = wolf->map_y + 1.0;
	}
	wolf->floor.dist_wall = wolf->perp_wall_dist;
	wolf->floor.dist_player = 0.0;
	draw_floor(wolf, x);
}

void	calc_wall(t_wolf *wolf, int x)
{
	wolf->texture->text_num = (wolf->map[wolf->map_x][wolf->map_y] - 1)\
	% TEXTNUM;
	if (wolf->side == 1)
		wolf->texture->text_num = (wolf->texture->text_num + 1) % TEXTNUM;
	if (wolf->side == 2)
		wolf->texture->text_num = (wolf->texture->text_num + 2) % TEXTNUM;
	if (wolf->side == 3)
		wolf->texture->text_num = (wolf->texture->text_num + 3) % TEXTNUM;
	if (wolf->side == 0 || wolf->side == 2)
		wolf->texture->wall_x = wolf->pos_y + wolf->perp_wall_dist\
		* wolf->raydir_y;
	else
		wolf->texture->wall_x = wolf->pos_x + wolf->perp_wall_dist\
	* wolf->raydir_x;
	wolf->texture->wall_x -= floor(wolf->texture->wall_x);
	wolf->texture->text_x = (int)(wolf->texture->wall_x * 64.0);
	if (wolf->side == 2 || wolf->side == 1)
		wolf->texture->text_x = 64 - wolf->texture->text_x - 1;
	calc_y(wolf, x);
}

void	calc_y(t_wolf *wolf, int x)
{
	int y;

	y = wolf->draw_start;
	while (y < wolf->draw_end)
	{
		wolf->texture->magic_d = y * 256 - HEIGHT * 128 +\
		wolf->line_height * 128;
		wolf->texture->text_y = ((wolf->texture->magic_d * 64)\
		/ wolf->line_height) / 256;
		wolf->color = get_pix_from_text(wolf->texture->wall_text\
		[wolf->texture->text_num], wolf->texture->text_x,\
		wolf->texture->text_y);
		ft_set_pixel(wolf, x, y);
		y++;
	}
}

void	calc_height(t_wolf *wolf)
{
	if (wolf->side == 0 || wolf->side == 2)
		wolf->perp_wall_dist = (wolf->map_x - wolf->pos_x + (1 - wolf->step_x)\
		/ 2) / wolf->raydir_x;
	else
		wolf->perp_wall_dist = (wolf->map_y - wolf->pos_y + (1 - wolf->step_y)\
			/ 2) / wolf->raydir_y;
	wolf->line_height = (int)(HEIGHT / wolf->perp_wall_dist);
	wolf->draw_start = -wolf->line_height / 2 + HEIGHT / 2;
	if (wolf->draw_start < 0)
		wolf->draw_start = 0;
	wolf->draw_end = wolf->line_height / 2 + HEIGHT / 2;
	if (wolf->draw_end >= HEIGHT)
		wolf->draw_end = HEIGHT - 1;
}
