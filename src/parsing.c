/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalexan <roalexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 20:00:51 by roalexan          #+#    #+#             */
/*   Updated: 2025/04/06 16:23:56 by roalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	parse_column(t_map *map, char **tab)
{
	int i = 0;
	int j;
	t_point3d point;

	j = -1;
	while(++j < map->col)
	{
		if (!ft_isdigit(*tab[j]) && *tab[j] != '-')
		{
			handle_error(3);
		}
		point.x = j * map->space - map->x_shift;
		point.y = i * map->space - map->y_shift;
		point.z = ft_atoi(tab[j]) * map->space;

		map->high_z = ft_max(map->high_z, point.z);
		map->low_z = ft_min(map->low_z, point.z);

		point.mapcolor = parse_color(tab[j], &point);
	}
}

void	parse_lines(int **row, char *str)
{
	char **split;
	int len;
	int i;

	i = 0;
	split = ft_split(str, ' ');
	if (!split)
		return ;
	len = file_lenght(*split);
	*row = (int *)ft_calloc(len, sizeof(int));
	if (!*row)
	{
		ft_free_split(split, sizeof(split));
		handle_error(-1);
	}
	while (split[i] && i < len)
	{
		(*row)[i] = ft_atoi(split[i]);
		++i;
	}
	ft_free_split(split, sizeof(split));
}

static void	allocate_grid2d(t_map *map)
{
	int i = 0;
	map->grid2d = (t_point2d **)malloc(sizeof(t_point2d *) * map->row);
	if (!map->grid2d)
		handle_error(-1);
	while (i < map->row)
	{
		map->grid2d[i] = (t_point2d *)malloc(sizeof(t_point2d) * map->col);
		if (!map->grid2d[i])
			handle_error(-1);
		i++;
	}
}

void	parse_map(t_map *map, char *filename)
{
	int	fd;
	char *line;
	int	i;

	i = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		handle_error(1);
	allocate_grid2d(map);
	line = get_next_line(fd);
	while (line != NULL)
	{
		process_line(map, line, i);
		i++;
		line = get_next_line(fd);
	}
	if (i < map->row)
	{
		free_map(map);
		handle_error(1);
	}
	project_2d(map);
	close (fd);
}
