/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalexan <roalexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 17:32:05 by roalexan          #+#    #+#             */
/*   Updated: 2025/04/09 20:58:41 by roalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	ft_loop_hook(void *param)
{
	t_fdf *fdf = param;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_ESCAPE) == true)
		clean_exit(fdf, fdf->rows);
}

void key_hook(mlx_key_data_t keydata, void *param)
{
    t_fdf *fdf = (t_fdf *)param;

    if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
    {
        if (keydata.key == MLX_KEY_UP)
            fdf->y_offset -= 10; // Move map up
        else if (keydata.key == MLX_KEY_DOWN)
            fdf->y_offset += 10; // Move map down
        else if (keydata.key == MLX_KEY_LEFT)
            fdf->x_offset -= 10; // Move map left
        else if (keydata.key == MLX_KEY_RIGHT)
            fdf->x_offset += 10; // Move map right
    }
}

