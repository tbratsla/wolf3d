/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbratsla <tbratsla@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/02 14:06:29 by tbratsla          #+#    #+#             */
/*   Updated: 2019/10/02 14:06:30 by tbratsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/wolf3d.h"

int		main(int ac, char **av)
{
	t_wolf	*wolf;

	if (ac == 2)
	{
		wolf = ft_read_map(av);
		game(wolf);
	}
	else
		ft_putendl("Error: wrong format!\nusage: ./wolf3d map_name");
	return (1);
}