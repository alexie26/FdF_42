/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalexan <roalexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 17:41:31 by roalexan          #+#    #+#             */
/*   Updated: 2025/04/24 17:52:36 by roalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../fdf.h"

void	draw_connect(t_fdf *fdf, int i, int j, int color1)
{
	t_line_data	line_data;
	t_point		p2;
	int			color2;

	color1 = fdf->three_d[i][j].color_val;
	if (j + 1 < fdf->size)
	{
		color2 = fdf->three_d[i][j + 1].color_val;
		p2 = project_isometric(fdf->three_d[i][j + 1], fdf);
		line_data.p1 = project_isometric(fdf->three_d[i][j], fdf);
		line_data.p2 = p2;
		line_data.color_a = color1;
		line_data.color_b = color2;
		draw_line(fdf, line_data, j, i);
	}
	if (i + 1 < fdf->rows)
	{
		color2 = fdf->three_d[i + 1][j].color_val;
		p2 = project_isometric(fdf->three_d[i + 1][j], fdf);
		line_data.p1 = project_isometric(fdf->three_d[i][j], fdf);
		line_data.p2 = p2;
		line_data.color_a = color1;
		line_data.color_b = color2;
		draw_line(fdf, line_data, j, i);
	}
}

void	draw_dots(t_fdf *fdf, int dist_x, int dist_y)
{
	int		i;
	int		j;
	t_point	p1;

	i = 0;
	(void)dist_x;
	(void)dist_y;
	while (i < fdf->rows)
	{
		while (j < fdf->size)
		{
			p1 = project_isometric(fdf->three_d[i][j], fdf);
			draw_connect(fdf, i, j, 0);
			j++;
		}
		j = 0;
		i++;
	}
}
