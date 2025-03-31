/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalexan <roalexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 20:00:51 by roalexan          #+#    #+#             */
/*   Updated: 2025/03/31 18:57:27 by roalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

int	parse_line(t_map *map, char *line)
{
	char **value;
	int i;

	i = 0;
	value = ft_split(line, ' ');
	if (!value)
		return (1);
	while (value[map->col] != NULL)
		map->col++;
	map->grid3d[map->row] = malloc(sizeof(t_point3d) * map->col);
	if (!map->grid3d[map->row])
	{
		perror("Error allocating memory for grid3d row");
		return (1);
	}
	while (i < map->col) //value into int and store them in grid3d
	{
		map->grid3d[map->row][i].z = ft_atoi(value[i]); //convert to int;
		map->grid3d[map->row][i].x = i;
		map->grid3d[map->row][i].y = map->row;
		if (map->row == 0 && i == 0)
		{
			map->high_z = map->grid3d[map->row][i].z;
			map->low_z = map->grid3d[map->row][i].z;
		}
		else
		{
			if (map->grid3d[map->row][i].z > map->high_z)
				map->high_z = map->grid3d[map->row][i].z;
			if (map->grid3d[map->row][i].z < map->low_z)
				map->low_z = map->grid3d[map->row][i].z;
		}
		i++;
	}
	while (value[i] != NULL)
		free(value[i]);
	free(value);
	return (0);
}

int	parse_mapfile(t_map *map, const char *filename)
{
	int fd;
	char *line;
	int row;

	row = 0;
	valid_file(filename);
	fd = open(filename, O_RDONLY);
	line = get_next_line(fd);
	while ((line != NULL))
	{
		if (row == 0)
		{
			map->grid3d = malloc(sizeof(t_point3d) * 1000); //1000 rows;
			if (!map->grid3d)
			{
				perror("Error allocating memory for grid3d");
				free(line);
				close(fd);
				return (1);
			}
		}
		if (parse_line(map, line) != 0)
		{
			free(line);
			close(fd);
			return (1);
		}
		free(line);
		line = get_next_line(fd);
		row++;
	}
	close(fd);
	map->row = row;
	return (0);
}

void parse_fdf_file(t_map *map, const char *filename)
{
    if (!valid_file(filename))
    {
        ft_printf("Invalid file or file cannot be opened.\n");
        exit(EXIT_FAILURE);
    }
    set_defaults(map);
    if (parse_mapfile(map, filename) != 0)
    {
        ft_printf("Error parsing the map file.\n");
        exit(EXIT_FAILURE);
    }
}