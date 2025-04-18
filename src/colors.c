/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalexan <roalexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 13:10:19 by roalexan          #+#    #+#             */
/*   Updated: 2025/04/18 17:54:39 by roalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

unsigned int	create_color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

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

unsigned int	zcolor(double perc)
{
	int	r;
	int	g;
	int	b;

	r = radiant(0, 255, perc);
	g = radiant(0, 255, 1.0 - perc);
	b = 255 - (int)(perc * 255);
	return (create_color(r, g, b, 255));
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
			fdf->three_d[i][j].color_val = zcolor(perc);
			j++;
		}
		i++;
	}
}

int	radiant(int start, int end, double percentage)
{
	return (int)((1 - percentage) * start + percentage * end);
}

unsigned int	get_gradient_color(t_point current, t_point a, t_point b,
		unsigned int color_a, unsigned int color_b)
{
	double	perc;

	int red, green, blue;
	if (color_a == color_b)
		return (color_a);
	if (abs(b.x - a.x) > abs(b.y - a.y))
		perc = percent(a.x, b.x, current.x);
	else
		perc = percent(a.y, b.y, current.y);
	red = radiant((color_a >> 24) & 0xFF, (color_b >> 24) & 0xFF, perc);
	green = radiant((color_a >> 16) & 0xFF, (color_b >> 16) & 0xFF, perc);
	blue = radiant((color_a >> 8) & 0xFF, (color_b >> 8) & 0xFF, perc);
	return (create_color(red, green, blue, 255));
}
