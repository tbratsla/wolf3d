/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbratsla <tbratsla@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/02 16:38:22 by tbratsla          #+#    #+#             */
/*   Updated: 2019/10/02 16:38:26 by tbratsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/wolf3d.h"

void	free_map(t_wolf *wolf, char **map)
{
	int i;

	i = 0;
	while (i < wolf->count_str)
	{
		free(map[i]);
		i++;
	}
	free(map);
}
