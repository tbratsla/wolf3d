/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbratsla <tbratsla@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 13:26:59 by tbratsla          #+#    #+#             */
/*   Updated: 2019/11/11 13:27:00 by tbratsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/wolf3d.h"

void	error(t_wolf *wolf, char **map, int k)
{
	if (k != wolf->count_num || wolf->count_num < 3)
	{
		free_map(wolf, map);
		ft_putendl("Error 3: wrong map format");
		exit(0);
	}
}

void	check_map_side2(t_wolf *wolf)
{
	int i;

	i = 0;
	while (i < wolf->count_num)
	{
		if (!wolf->map[wolf->count_str - 1][i])
		{
			ft_putendl("Error10: no side wall");
			exit(0);
		}
		i++;
	}
	i = 0;
	while (i < wolf->count_str)
	{
		if (!wolf->map[i][wolf->count_num - 1])
		{
			ft_putendl("Error10: no side wall");
			exit(0);
		}
		i++;
	}
}

void	check_map_side(t_wolf *wolf)
{
	int		i;

	i = 0;
	while (i < wolf->count_str)
	{
		if (!wolf->map[i][0])
		{
			ft_putendl("Error10: no side wall");
			exit(0);
		}
		i++;
	}
	i = 0;
	while (i < wolf->count_num)
	{
		if (!wolf->map[0][i])
		{
			ft_putendl("Error10: no side wall");
			exit(0);
		}
		i++;
	}
	check_map_side2(wolf);
}

void	ft_count_str(t_wolf *wolf, char **double_map)
{
	wolf->count_str = 0;
	while (double_map[wolf->count_str])
	{
		wolf->count_str++;
		if (wolf->count_str > 100)
		{
			free_map(wolf, double_map);
			free(wolf);
			ft_putendl("Error 5: to big map");
			exit(0);
		}
	}
	if (wolf->count_str < 3)
	{
		free_map(wolf, double_map);
		free(wolf);
		ft_putendl("Error 4: to small map");
		exit(0);
	}
}

void	ft_check_count_num(t_wolf *wolf, char **map)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	while (i < wolf->count_str)
	{
		j = 0;
		k = 0;
		while (map[i] && map[i][j])
		{
			while (map[i][j] && !ft_isdigit(map[i][j]))
				j++;
			if (ft_isdigit(map[i][j]))
			{
				k++;
				while (map[i][j] && ft_isdigit(map[i][j]))
					j++;
			}
		}
		error(wolf, map, k);
		i++;
	}
	check_all_lines(wolf, map);
}
