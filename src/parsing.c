/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalexan <roalexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 20:00:51 by roalexan          #+#    #+#             */
/*   Updated: 2025/04/08 20:21:10 by roalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

int	check_for_comma(char *line)
{
	int	i;

	i = 0;
	printf("%s\n", line);
	while (line[i])
	{
		if (line[i] == ',')
			return (1);
		i++;
	}
	return (0);
}

int get_size(char **array)
{
	int	count;
	count = 0;
	while (array && array[count])
			count++;
	return (count);
}

t_3d	*special_split(t_3d *fdf, char *line, int row)
{
	char **split;
	char **dif_split;
	int	i;
	
	split = ft_split(line, ' ');
	i = 0;
	while (split[i])
	{
		if (check_for_comma(split[i]) == 1)
		{
			dif_split = ft_split(split[i], ',');
			fdf[i].x = i;
			fdf[i].y = row;
			fdf[i].z = ft_atoi(dif_split[0]);
			fdf[i].color_val = ft_atoi(dif_split[1]);
			fdf[i].size = get_size(split);
			free(dif_split[0]);
			free(dif_split[1]);
			free(dif_split);
 		}
		else if (check_for_comma(split[i]) == 0)
		{
			fdf[i].x = i;
			fdf[i].y = row;
			fdf[i].z = ft_atoi(split[i]);
			fdf[i].color_val = 0xFF0000;
			fdf[i].size = get_size(split);
		}
		free(split[i]);
		i++;
		if (split[i] == NULL)
			break ;
	}
	free(split);
	return (fdf);
}

int get_rows(char *file)
{
	int fd = open(file, O_RDONLY);
	char *line = get_next_line(fd);
	int i = 0;
	while(line)
	{
		free(line);
		line = get_next_line(fd);
		i++;
	}
	free(line);
	close(fd);
	return (i);
}

t_fdf	*parse(char *filename)
{
	// remove("fdf_log.txt");
	int row = get_rows(filename);
	t_fdf *fdf = malloc(sizeof(t_fdf));
	fdf->three_d = malloc(sizeof(t_3d) * row);
	for(int i = 0; i < row; i++)
		fdf->three_d[i] = malloc(sizeof(t_3d) * MAX_WIDTH);
	int fd = open(filename, O_RDONLY);
	char *line = get_next_line(fd);
	int i = 0;
	while(i < row && line != NULL)
	{
		fdf->three_d[i] = special_split(fdf->three_d[i], line, i);
		free(line);
		line = get_next_line(fd);
		i++;
	}
	free(line);
	fdf->rows = row;
	return (fdf);
}