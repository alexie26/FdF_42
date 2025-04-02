/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalexan <roalexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 17:03:08 by roalexan          #+#    #+#             */
/*   Updated: 2025/04/02 20:34:20 by roalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	set_defaults(t_map *map)
{
	map->row = 0;
	map->col = 0;
	map->high_z = INT_MIN;
	map->low_z = INT_MAX;
	map->x_shift = WIDTH / 2;
	map->y_shift = HEIGHT / 2;
	map->space = 1;
	map->zoom = 1;
	map->xrotate = 0;
	map->yrotate = 0;
	map->zrotate = 0;
	map->grid2d = NULL;
	map->grid3d = NULL;
}

// static int	window(t_map *fdf)
// {
// 	mlx_set_setting(MLX_STRETCH_IMAGE, true);
// 	fractal->mlx = mlx_init(fractal->widht, fractal->height, "fract-ol", true);
// 	fractal->img = mlx_new_image(fractal->mlx, fractal->widht, fractal->height);
// 	mlx_image_to_window(fractal->mlx, fractal->img, 0, 0);
// 	mlx_loop_hook(fractal->mlx, &event_key, fractal);
// 	mlx_scroll_hook(fractal->mlx, &mouse_scroll, fractal);
// 	return (0);
// }