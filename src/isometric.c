/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalexan <roalexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 19:53:00 by roalexan          #+#    #+#             */
/*   Updated: 2025/04/17 16:48:41 by roalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

static void	transform_point(t_3d pt, t_fdf *fdf, double *x, double *y,
		double *z)
{
	*x = pt.x * fdf->zoom;
	*y = pt.y * fdf->zoom;
	*z = pt.z * fdf->z_scale;
	rotate_x(y, z, fdf->yrotate);
	rotate_y(x, z, fdf->yrotate);
	rotate_z(x, y, fdf->zrotate);
}

static t_point	apply_isometric_projection(double x, double y, double z,
		t_fdf *fdf)
{
	t_point	projected;
	double	cos_30;
	double	sin_30;

	cos_30 = cos(PI / 6);
	sin_30 = sin(PI / 6);
	projected.x = (int)((x - y) * cos_30) + fdf->x_offset;
	projected.y = (int)((x + y) * sin_30 - z) + fdf->y_offset;
	return (projected);
}

t_point	project_isometric(t_3d pt, t_fdf *fdf)
{
	double	x;
	double	y;
	double	z;

	transform_point(pt, fdf, &x, &y, &z);
	return (apply_isometric_projection(x, y, z, fdf));
}
