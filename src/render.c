/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalexan <roalexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 13:33:51 by roalexan          #+#    #+#             */
/*   Updated: 2025/04/08 12:56:40 by roalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"


int	calc_dot_dist_x(t_fdf *fdf)
{
	int	amount;
	int distance;

	amount = fdf->three_d[0][0].size;
	distance = (WIDTH + 50) / amount;
	return (distance);
}

int	calc_dot_dist_y(t_fdf *fdf)
{
	int	amount;
	int distance;

	amount = fdf->rows;
	distance = (HEIGHT - 50) / amount;
	return (distance);
}

void	draw_squares(t_fdf *fdf, int x, int y, int color)
{
	int	i = 0;
	int	j = 0;
	while(i < 9)
	{
		i++;
		while (j < 9)
		{
			j++;
			mlx_put_pixel(fdf->image,x + i, y + j, color);
		}
	}
}

void	draw_dots(t_fdf *fdf, int dist_x, int dist_y)
{
	int i;
	int	j;
	int	x;
	int	y;
	(void)dist_x;
	(void)dist_y;
	
	i = 0;
	j = 0;
	x = 50;
	y = 50;
	while (x < fdf->mlx->height - 50)
	{
		while(y < fdf->mlx->width - 50)
		{
			if (j > fdf->three_d[0][0].size)
			{
				j = 0;
				i++;
			}
			if (y % dist_y == 0 || x % dist_x == 0)
				mlx_put_pixel(fdf->image, x, y, 0xfffffff);
			if (y % dist_y == 0 && x % dist_x == 0)
			{
				mlx_put_pixel(fdf->image, x, y, fdf->three_d[i][j].color_val);
			}
		}
	}
}

int		render_map(t_fdf *fdf)
{
	int	x_dist;
	int	y_dist;

	x_dist = calc_dot_dist_x(fdf);
	y_dist = calc_dot_dist_y(fdf);
	// ft_printf("x_dist = %d\t\ty_dist = %d", x_dist, y_dist);
	draw_dots(fdf, x_dist, y_dist);
	//connnect dots
	return (1);
}
