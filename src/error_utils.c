/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalexan <roalexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 19:51:24 by roalexan          #+#    #+#             */
/*   Updated: 2025/04/14 15:53:20 by roalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	clean_exit(t_fdf *fdf, int row)
{
	int	i;

	i = 0;
	while (i < row)
	{
		free(fdf->three_d[i]);
		i++;
	}
	mlx_delete_image(fdf->mlx, fdf->image);
	mlx_terminate(fdf->mlx);
	exit(0);
}
