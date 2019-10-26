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

t_wolf		*ft_read_map(char **av)
{
	t_wolf	*wolf;
	int		fd;
	int		fd1;

	wolf = ft_memalloc(sizeof(t_wolf));
	if ((fd = open(av[1], O_RDONLY)) <= 0)
	{
		perror("Oh, no");
		close(fd);
		exit(0);
	}
	if ((fd1 = open(av[1], O_DIRECTORY)) > 0 || !ft_strcmp(av[1], "/dev/zero"))
	{
		ft_putendl("Are you crazy? Give me a valid map!");
		close(fd);
		close(fd1);
		exit(0);
	}
	close(fd1);
	ft_start_read(wolf, fd);
	return (wolf);
}

void	ft_start_read(t_wolf *wolf, int fd)
{
	char	*map;
	char	**double_map;
	char	*line;
	char	*tmp;
	int		i;

	map = ft_strnew(1);
	line = NULL;
	i = 0;
	while (get_next_line(fd, &line) > 0)
	{
		tmp = map;
		map = ft_strjoin(tmp, line);
		free(tmp);
		tmp = map;
		map = ft_strjoin(tmp, "\n");
		free(tmp);
		ft_strdel(&line);
		i++;
		if (i > 100 || ft_strlen(map) > 100000)
		{
			free(map);
			free(wolf);
			close(fd);
			ft_putendl("Error 6: to big map");
			exit(0);
		}
	}
	close(fd);
	double_map = ft_strsplit(map, '\n');
	free(map);
	ft_count_str(wolf, double_map);
	ft_check_map_format(wolf, double_map);
	ft_count_num(wolf, double_map);
	get_int_map(wolf, double_map);
}

void	ft_check_map_format(t_wolf *wolf, char **map)
{
	int		i;
	int		j;

	i = 0;
	while (i < wolf->count_str)
	{
		j = 0;
		while (map[i] && map[i][j])
		{
			if (!ft_isdigit(map[i][j]) && map[i][j] != ' ' && map[i][j] != '\n')
			{
				free_map(wolf, map);
				free(wolf);
				ft_putendl("Error 1: wrong map format");
				exit(0);
			}
			j++;
		}
		i++;
	}
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
				free(wolf);
				ft_putendl("Error 6: to big map");
				exit(0);
			}
			a = i;
			while (map[0][i] && ft_isdigit(map[0][i]))
				i++;
			if (i - a > 2)
			{
				free_map(wolf, map);
				free(wolf);
				ft_putendl("Error 7: to big number");
				exit(0);
			}
			if (map[0][i] && map[0][i] != ' ' && map[0][i] != '\n')
			{
				free_map(wolf, map);
				free(wolf);
				ft_putendl("Error 2: wrong map format");
				exit(0);
			}
		}
	}
	ft_check_count_num(wolf, map);
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
		if (k != wolf->count_num || wolf->count_num < 3)
		{
			free_map(wolf, map);
			free(wolf);
			ft_putendl("Error 3: wrong map format");
			exit(0);
		}
		i++;
	}
}

void	get_int_map(t_wolf *wolf, char **map)
{
	int		i;
	int		j;
	int		k;

	wolf->map = ft_memalloc(sizeof(int *) * wolf->count_str);
	i = 0;
	while (i < wolf->count_str)
	{
		wolf->map[i] = ft_memalloc(sizeof(int) * wolf->count_num);
		j = 0;
		k = 0;
		while (map[i] && map[i][k])
		{
			while (map[i][j] && !ft_isdigit(map[i][k]))
				k++;
			if (ft_isdigit(map[i][k]))
			{
				if (map[i][k] == '0' && ft_atoi(&map[i][k]) != 0)
				{
					free_map(wolf, map);
					free(wolf);
					ft_putendl("Error 8: wrong number format");
					exit(0);
				}
				wolf->map[i][j] = ft_atoi(&map[i][k]);
				j++;
				while (map[i][k] && ft_isdigit(map[i][k]))
					k++;
			}
		}
		i++;
	}
	free_map(wolf, map);
	i = 0;
	while (i < wolf->count_str)
	{
		j = 0;
		while (j < wolf->count_num)
		{
			ft_putnbr(wolf->map[i][j]);
			ft_putstr(" ");
			j++;
		}
		ft_putstr("\n");
		i++;
	}

}