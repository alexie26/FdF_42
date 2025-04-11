/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalexan <roalexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 17:32:05 by roalexan          #+#    #+#             */
/*   Updated: 2025/04/11 15:58:51 by roalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	ft_loop_hook(void *param)
{
	t_fdf *fdf = param;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_ESCAPE) == true)
		clean_exit(fdf, fdf->rows);
}

void	fdf_scrollhook(double xdelta, double ydelta, void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	if (ydelta > 0)
		fdf->zoom *= 1.02;
	else if (ydelta < 0 && fdf->zoom * 0.98 > 0)
		fdf->zoom *= 0.98;
	(void)xdelta;
	render_map(fdf);
}

void key_hook(mlx_key_data_t keydata, void *param)
{
    t_fdf *fdf = (t_fdf *)param;

    if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
    {
        if (keydata.key == MLX_KEY_UP)
            fdf->y_offset -= 5; // Move map up
        else if (keydata.key == MLX_KEY_DOWN)
            fdf->y_offset += 5; // Move map down
        else if (keydata.key == MLX_KEY_LEFT)
            fdf->x_offset -= 5; // Move map left
        else if (keydata.key == MLX_KEY_RIGHT)
            fdf->x_offset += 5; // Move map right
    }
}

void	ft_hook_rotate(void *param)
{
	t_fdf	*fdf;
	double	sign;

	fdf = (t_fdf *) param;
	sign = 0;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_COMMA))
		sign = -1;
	else if (mlx_is_key_down(fdf->mlx, MLX_KEY_PERIOD))
		sign = 1;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_S))
		fdf->z_scale += sign * 0.03;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_X))
		fdf->xrotate += sign * 0.02;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_Y))
		fdf->yrotate += sign * 0.02;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_Z))
		fdf->zrotate += sign * 0.02;
}


void	rotate_x(double *y, double *z, double alpha)
{
	double	previous_y;

	previous_y = *y;
	*y = previous_y * cos(alpha) + *z * sin(alpha);
	*z = -previous_y * sin(alpha) + *z * cos(alpha);
}

void	rotate_y(double *x, double *z, double beta)
{
	double	previous_x;

	previous_x = *x;
	*x = previous_x * cos(beta) + *z * sin(beta);
	*z = -previous_x * sin(beta) + *z * cos(beta);
}

void	rotate_z(double *x, double *y, double gamma)
{
	double	previous_x;
	double	previous_y;

	previous_x = *x;
	previous_y = *y;
	*x = previous_x * cos(gamma) - previous_y * sin(gamma);
	*y = previous_x * sin(gamma) + previous_y * cos(gamma);
}

