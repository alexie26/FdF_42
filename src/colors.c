/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalexan <roalexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 13:10:19 by roalexan          #+#    #+#             */
/*   Updated: 2025/04/22 20:44:17 by roalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"


int	radiant(int start, int end, double percentage)
{
	return ((int)((1 - percentage) * start + percentage * end));
}

double	percent(int start, int end, int current)
{
	double	placement;
	double	distance;

	placement = current - start;
	distance = end - start;
	if (distance == 0)
		return (1.0);
	return (placement / distance);
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
    return ((blue << 24) | (green << 16) | (red << 8) | 0xFF);
}

static int	zcolor(double perc)
{
	if (perc < 0.1)
		return (COLOR_ONE);
	else if (perc < 0.2)
		return (COLOR_TWO);
	else if (perc < 0.3)
		return (COLOR_THREE);
	else if (perc < 0.4)
		return (COLOR_FOUR);
	else if (perc < 0.5)
		return (COLOR_FIVE);
	else if (perc < 0.6)
		return (COLOR_SIX);
	else if (perc < 0.7)
		return (COLOR_SEVEN);
	else if (perc < 0.8)
		return (COLOR_EIGHT);
	else if (perc < 0.9)
		return (COLOR_NINE);
	else
		return (COLOR_TEN); 
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
