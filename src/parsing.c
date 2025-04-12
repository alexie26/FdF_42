/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalexan <roalexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 20:00:51 by roalexan          #+#    #+#             */
/*   Updated: 2025/04/12 21:33:20 by roalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	handle_comma_case(t_3d *fdf, char *split, int i, int row)
{
	char	**diff_split;

	diff_split = ft_split(split, ',');
	if (!diff_split || !diff_split[0] || !diff_split[1])
	{
		// Handle the error here, e.g.:
		ft_putstr_fd("Error: Invalid comma format in input.\n", 2);
		exit(1);  // or return, depending on your app
	}
	fdf[i].x = i;
	fdf[i].y = row;
	fdf[i].z = ft_atoi(diff_split[0]);
	fdf[i].color_val = atoi(diff_split[1]);
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
	fdf[i].color_val = 0xe5ccffff;
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
		{
			handle_comma_case(fdf, split[i], i, row);
		}
		else
		{
			handle_no_comma(fdf, split[i], i, row);
		}
		free(split[i]); // free AFTER handlers are done using it
		i++;
		if (split[i] == NULL)
			break ;
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
	t_fdf	*fdf;

	row = get_rows(filename);
	if (row == 0)
	{
    ft_putstr_fd("Error: Map has no rows.\n", 2);
    return (NULL);
	}
	fdf = malloc(sizeof(t_fdf));
	fdf->three_d = malloc(sizeof(t_3d *) * row);
	get_line_size_malloc(fdf, filename);
	fd = open(filename, O_RDONLY);
	line = get_next_line(fd);
	i = 0;
	while (i < row && line != NULL)
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
