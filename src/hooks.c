/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalexan <roalexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 17:32:05 by roalexan          #+#    #+#             */
/*   Updated: 2025/04/20 18:38:30 by roalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

static int	calculate_speed(int zoom)
{
	int	speed;

	if (zoom >= 0)
	{
		if (zoom > 25)
			speed = 25;
		else
			speed = zoom;
	}
	else
	{
		if ((zoom * -1) > 25)
			speed = 25;
		else
			speed = zoom * -1;
	}
	return (speed);
}

static void	handle_zoom(t_fdf *fdf)
{
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_MINUS))
	{
		fdf->zoom--;
		if (fdf->z_scale < 1)
			fdf->z_scale = 1;
	}
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_EQUAL))
		fdf->zoom++;
}

static void	handle_movement(t_fdf *fdf, int speed)
{
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_RIGHT))
		fdf->x_offset -= speed;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_LEFT))
		fdf->x_offset += speed;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_UP))
		fdf->y_offset -= speed;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_DOWN))
		fdf->y_offset += speed;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_KP_ADD))
		fdf->z_scale++;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_KP_SUBTRACT))
		fdf->z_scale--;
}

void	ft_loop_hook(void *param)
{
	t_fdf	*fdf;
	int		speed;

	fdf = param;
	speed = calculate_speed(fdf->zoom);
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_0))
	{
		fdf->xrotate = 0;
		fdf->yrotate = 0;
		fdf->zrotate = 0;
		fdf->z_scale = 1;
		fdf->zoom = 2;
	}
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_ESCAPE))
		clean_exit(fdf, fdf->rows);
	handle_zoom(fdf);
	handle_movement(fdf, speed);
}

void	ft_hook_rotate(void *param)
{
	t_fdf	*fdf;
	double	sign;

	fdf = (t_fdf *)param;
	sign = 0;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_COMMA))
		sign = -1;
	else if (mlx_is_key_down(fdf->mlx, MLX_KEY_PERIOD))
		sign = 1;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_X))
		fdf->xrotate += sign * 0.02;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_Y))
		fdf->yrotate += sign * 0.02;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_Z))
		fdf->zrotate += sign * 0.02;
}
