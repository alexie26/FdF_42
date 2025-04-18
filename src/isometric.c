/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isometric.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalexan <roalexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 19:53:00 by roalexan          #+#    #+#             */
/*   Updated: 2025/04/18 17:37:08 by roalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

static void	transform_point(t_3d pt, t_fdf *fdf, t_coords *coords)
{
	coords->x = pt.x * fdf->zoom;
	coords->y = pt.y * fdf->zoom;
	coords->z = pt.z * fdf->z_scale;
	rotate_x(&coords->y, &coords->z, fdf->yrotate);
	rotate_y(&coords->x, &coords->z, fdf->yrotate);
	rotate_z(&coords->x, &coords->y, fdf->zrotate);
}

static t_point	apply_isometric_projection(t_coords coords, t_fdf *fdf)
{
	t_point	projected;
	double	cos_30;
	double	sin_30;

	cos_30 = cos(PI / 6);
	sin_30 = sin(PI / 6);
	projected.x = (int)((coords.x - coords.y) * cos_30) + fdf->x_offset;
	projected.y = (int)((coords.x + coords.y) * sin_30 - coords.z)
		+ fdf->y_offset;
	return (projected);
}

t_point	project_isometric(t_3d pt, t_fdf *fdf)
{
	t_coords	coords;

	transform_point(pt, fdf, &coords);
	return (apply_isometric_projection(coords, fdf));
}
