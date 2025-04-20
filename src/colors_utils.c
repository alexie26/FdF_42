/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalexan <roalexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 17:59:51 by roalexan          #+#    #+#             */
/*   Updated: 2025/04/20 18:36:37 by roalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

static double	percent(int start, int end, int current)
{
	double	placement;
	double	distance;

	placement = current - start;
	distance = end - start;
	if (distance == 0)
		return (1.0);
	return (placement / distance);
}

void	set_zcolor(t_fdf *fdf, int min_z, int max_z)
{
	int		i;
	int		j;
	int		z;
	double	perc;

	i = 0;
	while (i < fdf->rows)
	{
		j = 0;
		while (j < fdf->size)
		{
			z = fdf->three_d[i][j].z;
			perc = percent(min_z, max_z, z);
			fdf->three_d[i][j].color_val = zcolor(perc, fdf->color);
			j++;
		}
		i++;
	}
}

unsigned int	zcolor(double perc, int color_mode)
{
	int	r;
	int	g;
	int	b;

	if (color_mode == 0)
	{
		r = radiant(0, 255, perc);
		g = radiant(0, 255, 1.0 - perc);
		b = 255 - (int)(perc * 255);
	}
	else if (color_mode == 1)
	{
		r = (int)(perc * 255);
		g = 100;
		b = 200;
	}
	else
	{
		r = (int)(perc * 255);
		g = (int)(perc * 255);
		b = (int)(perc * 255);
	}
	return (create_color(r, g, b, 255));
}

void	key_handler(void *param)
{
	t_fdf		*fdf;
	static bool	key_pressed = false;

	fdf = (t_fdf *)param;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_C))
	{
		if (!key_pressed)
		{
			key_pressed = true;
			fdf->color++;
			if (fdf->color > 2)
				fdf->color = 0;
			set_zcolor(fdf, fdf->min_z, fdf->max_z);
			render_map(fdf);
		}
	}
	else
		key_pressed = false;
}
