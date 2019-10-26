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
}