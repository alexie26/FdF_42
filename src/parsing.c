/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalexan <roalexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 20:00:51 by roalexan          #+#    #+#             */
/*   Updated: 2025/04/03 22:29:46 by roalexan         ###   ########.fr       */
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
void	parse_column(t_map *map, char **tab)
{
	int i = 0;
	int j;
	t_point3d point;

	j = -1;
	while(++j < map->col)
	{
		if (!ft_isdigit(*tab[j]) && *tab[j] != '-')
		{
			handle_error(3);
		}
		// point  = &(map->grid2d[i][j]);
		point.x = j * map->space - map->x_shift;
		point.y = i * map->space - map->y_shift;
		point.z = ft_atoi(tab[j]) * map->space;

		map->high_z = ft_max(map->high_z, point.z);
		map->low_z = ft_min(map->low_z, point.z);

		point.mapcolor = parse_color(tab[j], &point);
	}
}

void	parse_lines(int **row, char *str)
{
	char **split;
	int len;
	int i;

	i = 0;
	split = ft_split(str, ' ');
	if (!split)
		return ;
	len = file_lenght(*split);
	*row = (int *)ft_calloc(len, sizeof(int));
	if (!*row)
	{
		ft_free_split(split, sizeof(split));
		handle_error(-1);
	}
	while (split[i] && i < len)
	{
		(*row)[i] = ft_atoi(split[i]);
		++i;
	}
	ft_free_split(split, sizeof(split));
}


