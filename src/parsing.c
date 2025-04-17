/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalexan <roalexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 20:00:51 by roalexan          #+#    #+#             */
/*   Updated: 2025/04/17 21:22:15 by roalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	handle_comma_case(t_3d *fdf, char *split, int i, int row)
{
	char	**diff_split;

	diff_split = ft_split(split, ',');
	if (!diff_split || !diff_split[0] || !diff_split[1])
	{
		ft_putstr_fd("Error: Invalid comma format in input.\n", 2);
		exit(1);
	}
	fdf[i].x = i;
	fdf[i].y = row;
	fdf[i].z = ft_atoi(diff_split[0]);
	// fdf[i].color_val = ft_atoi(diff_split[1]);
	fdf[i].color_val = 0xffffffff;
	fdf[i].size = get_size(diff_split);
	free(diff_split[0]);
	free(diff_split[1]);
	free(diff_split);
}

void	handle_no_comma(t_3d *fdf, char *split, int i, int row)
{
	fdf[i].x = i;
	fdf[i].y = row;
	fdf[i].z = ft_atoi(split);
	fdf[i].color_val = 0xffffffff;
	// fdf[i].size = get_size(&split);
}

t_3d	*special_split(t_3d *fdf, char *line, int row)
{
	char	**split;
	int		i;

	split = ft_split(line, ' ');
	i = 0;
	while (split[i])
	{
		if (check_for_comma(split[i]) == 1)
			handle_comma_case(fdf, split[i], i, row);
		else
			handle_no_comma(fdf, split[i], i, row);
		free(split[i]);
		i++;
	}
	free(split);
	return (fdf);
}

t_fdf	*parse(char *filename)
{
	int		row;
	int		fd;
	int		i;
	char	*line;
	int		size;
	t_fdf	*fdf;
	char	**freesplit;
	char	**temp;

	row = get_rows(filename);
	if (row == 0)
		return (NULL);
	fdf = malloc(sizeof(t_fdf));
	fdf->three_d = malloc(sizeof(t_3d *) * row);
	if (!fdf->three_d)
	{
		free(fdf);
		return (NULL);
	}
	fd = open(filename, O_RDONLY);
	line = get_next_line(fd);
	temp = ft_split(line, ' ');
	fdf->size = get_size(temp);
	free_split(temp);
	fdf->rows = row;
	i = 0;
	while (i < row && line != NULL)
	{
		freesplit = ft_split(line, ' ');
		size = get_size(freesplit);
		free_split(freesplit);
		fdf->three_d[i] = malloc(sizeof(t_3d) * size);
		fdf->three_d[i] = special_split(fdf->three_d[i], line, i);
		free(line);
		line = get_next_line(fd);
		i++;
	}
	close(fd);
	free(line);
	return (fdf);
}
