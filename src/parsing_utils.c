/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalexan <roalexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 14:00:01 by roalexan          #+#    #+#             */
/*   Updated: 2025/04/13 16:52:30 by roalexan         ###   ########.fr       */
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

// int	get_rows(char *file)
// {
// 	int		fd;
// 	char	*line;
// 	int		i;
	
// 	line = 0;
// 	fd = open(file, O_RDONLY);
// 	i = 0;
// 	while (line)
// 	{
// 		free(line);
// 		line = get_next_line(fd);
// 		i++;
// 	}
// 	free(line);
// 	close(fd);
// 	return (i);
// }
int get_rows(char *file)
{
	int		fd;
	char	*line;
	int		i;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (-1); // error handling for file open

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


int	get_line_size(char *line)
{
	char	**split;
	int		i;

	split = ft_split(line, ' ');
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
	return (i);
}

void	get_line_size_malloc(t_fdf *fdf, char *filename)
{
	int		fd;
	char	*line;
	int		i;

	fd = open(filename, O_RDONLY);
	line = get_next_line(fd);
	i = 0;
	int k = 0;
	while (line)
	{
		printf("getlinesizeandmalloc:\t\t%d\n", k);
		k++;
		int size = get_line_size(line);
		fdf->three_d[i] = malloc(sizeof(t_3d) * size);
		fdf->three_d[i]->size = size;
		i++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	free(line);
}
