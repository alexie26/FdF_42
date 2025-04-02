/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalexan <roalexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 17:03:02 by roalexan          #+#    #+#             */
/*   Updated: 2025/04/02 20:33:55 by roalexan         ###   ########.fr       */
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

static void	draw_line(mlx_image_t *image, t_bresenham *bre, t_point2d a, t_point3d b)
{
	while (a.x != b.x || a.y != b.y)
	{
		if ((uint32_t)a.x < image->width
			&& (uint32_t)a.y < image->height)
			mlx_put_pixel(image, a.x, a.y, 0xFFFFFFF);
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

// When the error term is large in the x-direction,
// the algorithm moves in the x-direction.
// When the error term is large in the y-direction,
// the algorithm moves in the y-direction.