/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalexan <roalexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 16:49:50 by roalexan          #+#    #+#             */
/*   Updated: 2025/04/06 16:24:17 by roalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

int	parse_color(char *tok, t_point3d *point)
{
	int color;
	(void)point;
	// while (*token == '-')
	// 		token++;
	if (ft_strncmp(tok, "0x", 2) && ft_strncmp(tok, "0X", 2))
			return(0xFFFFFFF);
	tok += 2;
	ft_striteri(tok, &make_upper);
	color = ft_atoi_base(tok, 16);
	return ((color << 8) | 0xFF);
}

void	process_line(t_map *map, char *line, int row_indx)
{
	char **split;
	FILE *file = fopen("log.txt", "a");
	split = ft_split(line, ' ');
	int i = 0;
	(void)row_indx;
	if (!split)
	{
		free(line);
		free_map(map);
		handle_error(-1);
	}
	while(split[i])
	{
		// fprintf(file, "%s ", split[i]);
		fprintf(file, "%s\n", split[i]);
		i++;
	}
	fclose(file);
	parse_column(map, split);
	ft_free_split(split, map->col);
	free(line);
}
