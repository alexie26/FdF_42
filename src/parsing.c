/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalexan <roalexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 20:00:51 by roalexan          #+#    #+#             */
/*   Updated: 2025/04/09 15:13:26 by roalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

int	check_for_comma(char *line)
{
	// printf("%s\n", line);
	for (int i = 0; line[i]; i++)
		if (line[i] == ',')
			return (1);
	return (0);
}

int	get_size(char **array)
{
	int count = 0;
	while(array && array[count])
		count++;
	return (count);
}

t_3d *special_split(t_3d *fdf, char *line, int row)
{
	char **split = ft_split(line, ' ');
	// printf("%s\n", line);
	int i = 0;
	while(split[i])
	{
		if(check_for_comma(split[i]) == 1)
		{
			char **diff_split = ft_split(split[i], ',');
			fdf[i].x = i;
			fdf[i].y = row;
			fdf[i].z = ft_atoi(diff_split[0]);
			fdf[i].color_val = ft_atoi(diff_split[1]);
			fdf[i].size = get_size(split);
			free(diff_split[0]);
			free(diff_split[1]);
			free(diff_split);
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



int	get_line_size(char *line)
{
	char **split = ft_split(line, ' ');
	int i = 0;

	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
	return (i);
}


void	get_line_size_and_malloc(t_fdf *fdf, char *filename)
{
	int fd = open(filename, O_RDONLY);
	char *line = get_next_line(fd);
	int i = 0;
	while(line)
	{
		fdf->three_d[i] = malloc(sizeof(t_3d) * get_line_size(line));
		fdf->three_d[i]->size = get_line_size(line);
		i++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
}

t_fdf	*parse(char *filename)
{
	// remove("fdf_log.txt");
	int row = get_rows(filename);
	t_fdf *fdf = malloc(sizeof(t_fdf));
	fdf->three_d = malloc(sizeof(t_3d *) * row);
	// for(int i = 0; i < row; i++)
	// 	fdf->three_d[i] = malloc(sizeof(t_3d) * MAX_WIDTH);
	get_line_size_and_malloc(fdf, filename);
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

// t_fdf	*parse(char *filename)
// {
// 	// remove("fdf_log.txt");
// 	int row = get_rows(filename);
// 	t_fdf *fdf = malloc(sizeof(t_fdf));
// 	fdf->three_d = malloc(sizeof(t_3d) * row);
// 	for(int i = 0; i < row; i++)
// 		fdf->three_d[i] = malloc(sizeof(t_3d) * MAX_WIDTH);
// 	int fd = open(filename, O_RDONLY);
// 	char *line = get_next_line(fd);
// 	int i = 0;
// 	while(i < row && line)
// 	{
// 		fdf->three_d[i] = special_split(fdf->three_d[i], line, i);
// 		free(line);
// 		line = get_next_line(fd);
// 		i++;
// 	}
// 	free(line);
// 	fdf->rows = row;
// 	return (fdf);
// }