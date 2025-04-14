/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalexan <roalexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 17:32:05 by roalexan          #+#    #+#             */
/*   Updated: 2025/04/14 18:30:38 by roalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	ft_loop_hook(void *param)
{
	t_fdf	*fdf;
	int		speed;

	fdf = param;
	if (fdf->zoom >= 0)
		speed = fdf->zoom;
	else
		speed = fdf->zoom * -1;
	// printf("speed%d\n", speed);
	if (speed > 25)
		speed = 25;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_ESCAPE) == true)
		clean_exit(fdf, fdf->rows);
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_LEFT))
	{
		fdf->zoom--;
		fdf->z_scale--;
		if (fdf->z_scale < 1)
			fdf->z_scale = 1;
	}
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_RIGHT))
	{
		fdf->zoom++;
		fdf->z_scale++ ;
	}
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_A))
		fdf->x_offset -= speed;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_D))
		fdf->x_offset += speed;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_W))
		fdf->y_offset -= speed;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_S))
		fdf->y_offset += speed;
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
