/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalexan <roalexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 20:00:51 by roalexan          #+#    #+#             */
/*   Updated: 2025/04/24 17:48:55 by roalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../fdf.h"

static t_fdf	*allocate_fdf(int row)
{
	t_fdf	*fdf;

	fdf = malloc(sizeof(t_fdf));
	if (!fdf)
		return (NULL);
	fdf->three_d = malloc(sizeof(t_3d *) * row);
	if (!fdf->three_d)
	{
		free(fdf);
		return (NULL);
	}
	return (fdf);
}

void	initialize_fdf(t_fdf *fdf, char *line, int row)
{
	char	**temp;

	temp = ft_split(line, ' ');
	if (!temp)
	{
		ft_putstr_fd("Error: Memory allocation failed.\n", 2);
		return ;
	}
	fdf->size = get_size(temp);
	free_split(temp);
	fdf->rows = row;
}

void	process_file_line(t_fdf *fdf, char *line, int row)
{
	char	**freesplit;
	int		size;

	freesplit = ft_split(line, ' ');
	size = get_size(freesplit);
	free_split(freesplit);
	fdf->three_d[row] = malloc(sizeof(t_3d) * size);
	fdf->three_d[row] = special_split(fdf->three_d[row], line, row);
	free(line);
}

t_fdf	*parse(char *filename, int i)
{
	int		row;
	int		fd;
	char	*line;
	t_fdf	*fdf;

	row = get_rows(filename);
	if (row == 0)
		return (NULL);
	fdf = allocate_fdf(row);
	if (!fdf)
		return (NULL);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	line = get_next_line(fd);
	if (!line)
		return (close(fd), NULL);
	initialize_fdf(fdf, line, row);
	while (++i < row && line != NULL)
	{
		process_file_line(fdf, line, i);
		line = get_next_line(fd);
	}
	return (close(fd), free(line), fdf);
}

// t_fdf	*parse(char *filename)
// {
// 	int		row;
// 	int		fd;
// 	int		i;
// 	char	*line;
// 	int		size;
// 	t_fdf	*fdf;
// 	char	**freesplit;
// 	char	**temp;

// 	row = get_rows(filename);
// 	if (row == 0)
// 		return (NULL);
// 	fdf = malloc(sizeof(t_fdf));
// 	fdf->three_d = malloc(sizeof(t_3d *) * row);
// 	if (!fdf->three_d)
// 	{
// 		free(fdf);
// 		return (NULL);
// 	}
// 	fd = open(filename, O_RDONLY);
// 	line = get_next_line(fd);
// 	temp = ft_split(line, ' ');
// 	fdf->size = get_size(temp);
// 	free_split(temp);
// 	fdf->rows = row;
// 	i = 0;
// 	while (i < row && line != NULL)
// 	{
// 		freesplit = ft_split(line, ' ');
// 		size = get_size(freesplit);
// 		free_split(freesplit);
// 		fdf->three_d[i] = malloc(sizeof(t_3d) * size);
// 		fdf->three_d[i] = special_split(fdf->three_d[i], line, i);
// 		free(line);
// 		line = get_next_line(fd);
// 		i++;
// 	}
// 	close(fd);
// 	free(line);
// 	return (fdf);
// }
