/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalexan <roalexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 13:33:51 by roalexan          #+#    #+#             */
/*   Updated: 2025/04/09 20:54:32 by roalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	init(t_fdf *fdf)
{
    double	cos_30 = cos(PI / 6);  // cos(30 degrees)
    double	sin_30 = sin(PI / 6);  // sin(30 degrees)
    int		map_width;
    int		map_height;

    // Set zoom and z_scale
    fdf->zoom = 4;
    fdf->z_scale = 2;

    // Calculate map dimensions in isometric projection
    map_width = (fdf->three_d[0][0].size - 1) * fdf->zoom * cos_30;
    map_height = ((fdf->rows - 1) * fdf->zoom * sin_30) - ((fdf->rows - 1) * fdf->z_scale);

    // Center the map in the window
    fdf->x_offset = (WIDTH - map_width) / 2;
    fdf->y_offset = (HEIGHT - map_height) / 2;
}
int	calc_dot_dist_x(t_fdf *fdf)
{
	int	amount;
	int distance;

	amount = fdf->three_d[0][0].size;
	distance = (WIDTH - 50) / amount;
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



t_point project_isometric(t_3d pt, t_fdf *fdf)
{
    t_point projected;

    double x = pt.x * fdf->zoom;
    double y = pt.y * fdf->zoom;
    double z = pt.z * fdf->z_scale;

    double cos_30 = cos(PI / 6);  
    double sin_30 = sin(PI / 6);  

    // Apply isometric projection
    projected.x = (int)((x - y) * cos_30) + fdf->x_offset;
    projected.y = (int)((x + y) * sin_30 - z) + fdf->y_offset;

    // Print for debugging (optional)
    // printf("Projected point: (%d, %d)\n", projected.x, projected.y);

    return projected;
}

void	draw_dots(t_fdf *fdf, int dist_x, int dist_y)
{
	int		i = 0;
	int		j = 0;
	t_point	p1, p2;

	(void)dist_x;
	(void)dist_y;
	init(fdf);
	while (i < fdf->rows)
	{
		j = 0;
		while (j < fdf->three_d[0][0].size)
		{
			p1 = project_isometric(fdf->three_d[i][j], fdf);

			// Connect to the right neighbor
			if (j + 1 < fdf->three_d[0][0].size)
			{
				p2 = project_isometric(fdf->three_d[i][j + 1], fdf);
				draw_line(fdf, p1, p2, fdf->three_d[i][j].color_val);
			}

			// Connect to the bottom neighbor
			if (i + 1 < fdf->rows)
			{
				p2 = project_isometric(fdf->three_d[i + 1][j], fdf);
				draw_line(fdf, p1, p2, fdf->three_d[i][j].color_val);
			}
			j++;
		}
		i++;
	}
}


void	draw_line(t_fdf *fdf, t_point p1, t_point p2, int color)
{
	int dx = abs(p2.x - p1.x);
	int dy = -abs(p2.y - p1.y);
	int sx = (p1.x < p2.x) ? 1 : -1;
	int sy = (p1.y < p2.y) ? 1 : -1;
	int err = dx + dy;
	int e2;
	(void)color;
	while (1)
	{
		if (p1.x >= 0 && p1.x < fdf->mlx->width && p1.y >= 0 && p1.y < fdf->mlx->height)
			mlx_put_pixel(fdf->image, p1.x, p1.y, 0xffffffff);
		if (p1.x == p2.x && p1.y == p2.y)
			break;
		e2 = 2 * err;
		if (e2 >= dy)
		{
			err += dy;
			p1.x += sx;
		}
		if (e2 <= dx)
		{
			err += dx;
			p1.y += sy;
		}
		// printf("%d--%d--%d--%d\n", p1.x, p1.y, p2.x, p2.y);
	}
}

int		render_map(t_fdf *fdf)
{
	int	x_dist;
	int	y_dist;

	x_dist = calc_dot_dist_x(fdf);
	y_dist = calc_dot_dist_y(fdf);
	fdf->image = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
	mlx_image_to_window(fdf->mlx, fdf->image, 0, 0);

		draw_dots(fdf, x_dist, y_dist);
	//connnect dots
	return (1);
}
