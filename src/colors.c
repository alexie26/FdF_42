/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalexan <roalexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 13:10:19 by roalexan          #+#    #+#             */
/*   Updated: 2025/04/20 18:38:06 by roalexan         ###   ########.fr       */
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

int	radiant(int start, int end, double percentage)
{
	return ((int)((1 - percentage) * start + percentage * end));
}

unsigned int	get_gradient_color(t_point current, t_grad gradient)
{
	double	perc;
	int		red;
	int		green;
	int		blue;

	if (gradient.color_a == gradient.color_b)
		return (gradient.color_a);
	if (abs(gradient.b.x - gradient.a.x) > abs(gradient.b.y - gradient.a.y))
		perc = percent(gradient.a.x, gradient.b.x, current.x);
	else
		perc = percent(gradient.a.y, gradient.b.y, current.y);
	red = radiant((gradient.color_a >> 24) & 0xFF,
			(gradient.color_b >> 24) & 0xFF, perc);
	green = radiant((gradient.color_a >> 16) & 0xFF,
			(gradient.color_b >> 16) & 0xFF, perc);
	blue = radiant((gradient.color_a >> 8) & 0xFF,
			(gradient.color_b >> 8) & 0xFF, perc);
	return (create_color(red, green, blue, 255));
}
