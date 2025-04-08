/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalexan <roalexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 17:32:05 by roalexan          #+#    #+#             */
/*   Updated: 2025/04/08 10:53:07 by roalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	ft_loop_hook(void *param)
{
	t_fdf *fdf = param;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_ESCAPE) == true)
		clean_exit(fdf, fdf->rows);
}
