/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalexan <roalexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 14:00:01 by roalexan          #+#    #+#             */
/*   Updated: 2025/04/16 16:43:28 by roalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

int	check_for_comma(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == ',')
			return (1);
		i++;
	}
	return (0);
}

int	get_size(char **array)
{
	int	count;

	count = 0;
	while (array && array[count])
		count++;
	return (count);
}

int	get_rows(char *file)
{
	int		fd;
	char	*line;
	int		i;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (-1);
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		i++;
	}
	close(fd);
	return (i);
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return ;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	get_line_size_malloc(t_fdf *fdf, char *lines, int row_count)
{
	int		i;
	char	**split;
	int		size;
	int		fd;
	char	*line;

	fd = open(lines, O_RDONLY);
	line = get_next_line(fd);
	fdf->three_d = malloc(sizeof(t_3d *) * row_count);
	i = 0;
	while (i < row_count)
	{
		split = ft_split(&lines[i], ' ');
		size = get_size(split);
		fdf->three_d[i] = malloc(sizeof(t_3d *) * size);
		line = get_next_line(fd);
		free_split(split);
		i++;
	}
	close(fd);
	fdf->rows = row_count;
}
