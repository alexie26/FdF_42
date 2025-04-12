/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalexan <roalexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 15:01:35 by roalexan          #+#    #+#             */
/*   Updated: 2025/04/12 20:56:10 by roalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

int	calc_dot_dist_x(t_fdf *fdf)
{
	int	amount;
	int distance;

	amount = fdf->three_d[0][0].size;
	if (amount == 0)
    {
        ft_putstr_fd("Error: Number of columns is zero.\n", 2);
        return (0); // Return 0 or handle the error as needed
    }
	distance = (WIDTH - 50) / amount;
	return (distance);
}

int	calc_dot_dist_y(t_fdf *fdf)
{
	int	amount;
	int distance;

	amount = fdf->rows;
	if (amount == 0)
    {
        ft_putstr_fd("Error: Number of rows is zero.\n", 2);
        return (0); // Return 0 or handle the error as needed
    }
	distance = (HEIGHT - 50) / amount;
	return (distance);
}

void	draw_squares(t_fdf *fdf, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
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

void	rotate_point(int *x, int *y, t_fdf *fdf)
{
	float	x_new;
	float	y_new;
	float	center_x;
	float	center_y;
	
	center_x = (fdf->three_d[0][0].size - 1) * fdf->zoom / 2.0;
	center_y = (fdf->rows - 1) * fdf->zoom / 2.0;

	*x -= center_x;
	*y -= center_y;

	x_new = *x * cos(fdf->zrotate) - *y * sin(fdf->zrotate);
	y_new = *x * sin(fdf->zrotate) + *y * cos(fdf->zrotate);

	*x = x_new + center_x;
	*y = y_new + center_y;
}

