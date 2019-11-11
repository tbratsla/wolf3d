/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbratsla <tbratsla@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/02 14:21:22 by tbratsla          #+#    #+#             */
/*   Updated: 2019/10/02 14:21:24 by tbratsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/wolf3d.h"
#include <stdio.h>

void	check_all_lines(t_wolf *wolf, char **map)
{
	int	i;
	int	j;
	int	a;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			while (map[i][j] && !ft_isdigit(map[i][j]))
				j++;
			a = j;
			while (map[i][j] && ft_isdigit(map[i][j]))
				j++;
			if (j - a > 2)
			{
				free_map(wolf, map);
				ft_putendl("Error 7: to big number");
				exit(0);
			}
		}
		i++;
	}
}

void	digit_error(t_wolf *wolf, char **map, int i, int j[2])
{
	if (map[i][j[1]] == '0' && ft_atoi(&map[i][j[1]]) != 0)
	{
		free_map(wolf, map);
		ft_putendl("Error 8: wrong number format");
		exit(0);
	}
}

void	count_num_errors(t_wolf *wolf, char **map, int i, int a)
{
	if (i - a > 2)
	{
		free_map(wolf, map);
		ft_putendl("Error 7: to big number");
		exit(0);
	}
	if (map[0][i] && map[0][i] != ' ' && map[0][i] != '\n')
	{
		free_map(wolf, map);
		ft_putendl("Error 2: wrong map format");
		exit(0);
	}
}

void	ft_count_num(t_wolf *wolf, char **map)
{
	int i;
	int	a;

	i = 0;
	while (map[0] && map[0][i])
	{
		while (map[0][i] && !ft_isdigit(map[0][i]))
			i++;
		if (ft_isdigit(map[0][i]))
		{
			wolf->count_num++;
			if (wolf->count_num > 100)
			{
				free_map(wolf, map);
				ft_putendl("Error 6: to big map");
				exit(0);
			}
			a = i;
			while (map[0][i] && ft_isdigit(map[0][i]))
				i++;
			count_num_errors(wolf, map, i, a);
		}
	}
	ft_check_count_num(wolf, map);
}

void	get_int_map(t_wolf *wolf, char **map)
{
	int		i;
	int		j[2];

	wolf->map = ft_memalloc(sizeof(int *) * wolf->count_str);
	i = 0;
	while (i < wolf->count_str)
	{
		wolf->map[i] = ft_memalloc(sizeof(int) * wolf->count_num);
		j[0] = 0;
		j[1] = 0;
		while (map[i] && map[i][j[1]])
		{
			while (map[i][j[1]] && !ft_isdigit(map[i][j[1]]))
				j[1]++;
			if (ft_isdigit(map[i][j[1]]))
			{
				digit_error(wolf, map, i, j);
				wolf->map[i][j[0]] = ft_atoi(&map[i][j[1]]);
				j[0]++;
				while (map[i][j[1]] && ft_isdigit(map[i][j[1]]))
					j[1]++;
			}
		}
		i++;
	}
}
