/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalexan <roalexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 13:33:51 by roalexan          #+#    #+#             */
/*   Updated: 2025/04/06 17:14:28 by roalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	draw_map(t_fdf *fdf)
{
	int	i;
	int	j = 0;
	t_map *map = fdf->map;

	i = 0;
	while (i < map->row)
	{
		while(j < map->col)
			{
				printf("Rows: %d, Cols: %d\n", map->row, map->col);

				if (j < map->col - 1)
					bresenham(fdf->image, map->grid2d[i][j], map->grid3d[i][j]);
				if (i < map->col - 1)
					bresenham(fdf->image, map->grid2d[i][j], map->grid3d[i][j]);
			j++;
			}
		i++;
		j = 0;
		}
	
	}