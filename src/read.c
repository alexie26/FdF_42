/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalexan <roalexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 14:43:41 by roalexan          #+#    #+#             */
/*   Updated: 2025/04/24 14:44:20 by roalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include ".../fdf.h"

static char	**expand_lines_array(char **old, int *capacity)
{
	char	**new_array;
	int		i;

	*capacity *= 2;
	new_array = malloc(sizeof(char *) * (*capacity));
	if (!new_array)
		return (NULL);
	i = 0;
	while (old[i])
	{
		new_array[i] = old[i];
		i++;
	}
	new_array[i] = NULL;
	free(old);
	return (new_array);
}

char	**read_file_lines(char *filename, int *out_row)
{
	int		fd;
	char	*line;
	char	**lines;
	int		capacity;
	int		i;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	capacity = 128;
	lines = malloc(sizeof(char *) * capacity);
	if (!lines)
		return (NULL);
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (i >= capacity)
			lines = expand_lines_array(lines, &capacity);
		lines[i++] = line;
		line = get_next_line(fd);
	}
	lines[i] = NULL;
	*out_row = i;
	return (close(fd), lines);
}
