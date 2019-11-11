/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_help.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbratsla <tbratsla@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 13:48:36 by tbratsla          #+#    #+#             */
/*   Updated: 2019/11/11 13:48:37 by tbratsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/wolf3d.h"

void	main_gnl_cycle(char **line, char **map, int fd, int *i)
{
	char *tmp;

	tmp = *map;
	*map = ft_strjoin(tmp, *line);
	free(tmp);
	tmp = *map;
	*map = ft_strjoin(tmp, "\n");
	free(tmp);
	ft_strdel(&(*line));
	(*i)++;
	if ((*i) > 100 || ft_strlen(*map) > 100000)
	{
		free(*map);
		close(fd);
		ft_putendl("Error 6: to big map");
		exit(0);
	}
}

t_wolf	*ft_read_map(char **av)
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
	int		i;

	map = ft_strnew(1);
	line = NULL;
	i = 0;
	while (get_next_line(fd, &line) > 0)
		main_gnl_cycle(&line, &map, fd, &i);
	close(fd);
	double_map = ft_strsplit(map, '\n');
	free(map);
	ft_count_str(wolf, double_map);
	ft_check_map_format(wolf, double_map);
	ft_count_num(wolf, double_map);
	get_int_map(wolf, double_map);
	free_map(wolf, double_map);
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
