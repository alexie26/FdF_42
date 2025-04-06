/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalexan <roalexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 17:03:02 by roalexan          #+#    #+#             */
/*   Updated: 2025/04/06 17:15:48 by roalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

static void	initalize(t_bresenham *bre, t_point2d a, t_point3d b)
{
	bre->dx = fabs(b.x - a.x);
	bre->dy = fabs(b.y - a.y);
	if (a.x < b.x)
		bre->sx = 1;
	else
		bre->sx = -1;
	if (a.y < b.y)
		bre->sy = 1;
	else
		bre->sy = -1;
	bre->error[0] = bre->dx - bre->dy;
}
static void		isometric(double *x, double *y, double z)
{
	double	tmp_x;
	double	tmp_y;
	
	tmp_x = *x;
	tmp_y = *y;
	*x = (tmp_x - tmp_y) * cos(0.523599); //30
	*y = (tmp_x + tmp_y) * sin(0.523599) - z;
	
}

void	project_2d(t_map *map)
{
	int	i = 0;
	int	j = 0;
	t_point3d point;
	t_point2d *proj;

	while (i < map->row)
	{
		while(j < map->col)
		{
			printf("Projected point: (%f, %f)\n", proj->x, proj->y);
			point = map->grid3d[i][j];
			proj = &map->grid2d[i][j];
			
			proj->x = point.x * map->space;
			proj->y = point.y * map->space;
			proj->z = point.z;

			isometric(&proj->x, &proj->y, proj->z);

			proj->x += map->x_shift;
			proj->y += map->y_shift;
			proj->mapcolor = point.mapcolor;
		}
	}
}

static void	draw_line(mlx_image_t *image, t_bresenham *bre, t_point2d a, t_point3d b)
{
	while (a.x != b.x || a.y != b.y)
	{
		printf("Pixel: (%d, %d)\n", (int)a.x, (int)a.y);
		if ((uint32_t)a.x < image->width
			&& (uint32_t)a.y < image->height)
			mlx_put_pixel(image, a.x, a.y, 0xFFFFFFFF);
		bre->error[1] = 2 * bre->error[0];
		if (bre->error[1] > -bre->dy)
		{
			bre->error[0] -= bre->dy;
			a.x += bre->sx;
		}
		if (bre->error[1] < bre->dx)
		{
			bre->error[0] += bre->dx;
			a.y += bre->sy;
		}
	}
}

void	bresenham(mlx_image_t *image, t_point2d a, t_point3d b)
{
	t_bresenham	bre;
	t_point2d	current;
	
	current.x = a.x;
	current.y = a.y;
	initalize(&bre, a, b);
	draw_line(image, &bre, current, b);
}

