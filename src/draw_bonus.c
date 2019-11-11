/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbratsla <tbratsla@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 12:14:03 by tbratsla          #+#    #+#             */
/*   Updated: 2019/11/11 12:14:04 by tbratsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/wolf3d.h"

void	draw_fps(t_wolf *wolf)
{
	SDL_Color	color;
	SDL_Surface	*message;
	SDL_Rect	f;
	char		*fps;

	fps = ft_itoa((int)(100.0 / wolf->time));
	f.x = 50;
	f.y = 50;
	color = (SDL_Color){100, 10, 10, 0};
	message = TTF_RenderText_Solid(wolf->font, fps, color);
	SDL_BlitSurface(message, NULL, SDL_GetWindowSurface(wolf->win), &f);
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
	while (x < WIDTH / 2 + 10)
	{
		ft_set_pixel(wolf, x, y);
		x++;
	}
	x = WIDTH / 2;
	y = HEIGHT / 2 - 10;
	while (y < HEIGHT / 2 + 10)
	{
		ft_set_pixel(wolf, x, y);
		y++;
	}
}

void	draw_floor(t_wolf *wolf, int x)
{
	int y;

	if (wolf->draw_end < 0)
		wolf->draw_end = HEIGHT;
	y = wolf->draw_end + 1;
	while (y < HEIGHT)
	{
		wolf->floor.current_dist = HEIGHT / (2.0 * y - HEIGHT);
		wolf->floor.weight = (wolf->floor.current_dist -\
		wolf->floor.dist_player) / (wolf->floor.dist_wall -\
		wolf->floor.dist_player);
		wolf->floor.cur_floor_x = wolf->floor.weight *\
		wolf->floor.floor_x_wall + (1.0 - wolf->floor.weight) * wolf->pos_x;
		wolf->floor.cur_floor_y = wolf->floor.weight * wolf->floor.floor_y_wall\
		+ (1.0 - wolf->floor.weight) * wolf->pos_y;
		wolf->floor.floor_tex_x = (int)(wolf->floor.cur_floor_x * 64) % 64;
		wolf->floor.floor_tex_y = (int)(wolf->floor.cur_floor_y * 64) % 64;
		wolf->color = get_pix_from_text(wolf->texture->floor_text[0],\
		wolf->floor.floor_tex_x, wolf->floor.floor_tex_y);
		ft_set_pixel(wolf, x, y);
		wolf->color = get_pix_from_text(wolf->texture->floor_text[1],\
			wolf->floor.floor_tex_x, wolf->floor.floor_tex_y);
		ft_set_pixel(wolf, x, HEIGHT - y);
		y++;
	}
}
