/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalexan <roalexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 13:10:19 by roalexan          #+#    #+#             */
/*   Updated: 2025/04/17 19:22:39 by roalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

unsigned int create_color(uint8_t r,uint8_t g, uint8_t b, uint8_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

static double percent (int start, int end, int current)
{
	double placement;
	double distance;

	placement = current - start;
	distance = end - start;
	if (distance == 0)
		return (1.0);
	return (placement / distance);
}

unsigned int zcolor(double perc)
{
	int r = radiant(0, 255, perc);     // From black to red
	int g = radiant(0, 255, 1.0 - perc); // From green to black
	int b = 255 - (int)(perc * 255);   // From blue to black
	return create_color(r, g, b, 255);
}

void set_zcolor(t_fdf *fdf, int min_z, int max_z)
{
	for (int i = 0; i < fdf->rows; i++)
	{
		for (int j = 0; j < fdf->size; j++)
		{
			int z = fdf->three_d[i][j].z;
			double perc = percent(min_z, max_z, z);
			fdf->three_d[i][j].color_val = zcolor(perc);
		}
	}
}

int radiant(int start, int end, double percentage)
{
	return (int)((1 - percentage) * start + percentage * end);
}

unsigned int get_gradient_color(t_point current, t_point a, t_point b, unsigned int color_a, unsigned int color_b)
{
	int red, green, blue;
	double perc;

	if (color_a == color_b)
		return color_a;

	if (abs(b.x - a.x) > abs(b.y - a.y))
		perc = percent(a.x, b.x, current.x);
	else
		perc = percent(a.y, b.y, current.y);
		// printf("%d\t\t%d\t\t%d\n", b.x, a.x, current.x);

	red   = radiant((color_a >> 24) & 0xFF, (color_b >> 24) & 0xFF, perc);
	green = radiant((color_a >> 16) & 0xFF, (color_b >> 16) & 0xFF, perc);
	blue  = radiant((color_a >> 8)  & 0xFF, (color_b >> 8)  & 0xFF, perc);

	return create_color(red, green, blue, 255);
}

// void	set_zcolor(t_fdf *fdf)
// {
// 	int	i;
// 	int	j;
// 	double	perc;

// 	i = -1;
// 	while (++i < fdf->rows)
// 	{
// 		j = -1;
// 		while (++j < fdf->size)
// 		{
// 			perc = percent(fdf->)
// 		}
// 	}
// }