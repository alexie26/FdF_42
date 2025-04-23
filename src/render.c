/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalexan <roalexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 13:33:51 by roalexan          #+#    #+#             */
/*   Updated: 2025/04/23 19:43:53 by roalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

static void	draw_connect(t_fdf *fdf, int i, int j, int color1)
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

void	initialize_line(t_point p1, t_point p2, t_line *line)
{
	line->dx = abs(p2.x - p1.x);
	line->dy = -abs(p2.y - p1.y);
	if (p1.x < p2.x)
		line->sx = 1;
	else
		line->sx = -1;
	if (p1.y < p2.y)
		line->sy = 1;
	else
		line->sy = -1;
	line->err = line->dx + line->dy;
}

void	update_line(t_point *p1, t_line *line)
{
	int	e2;

	e2 = 2 * line->err;
	if (e2 >= line->dy)
	{
		line->err += line->dy;
		p1->x += line->sx;
	}
	if (e2 <= line->dx)
	{
		line->err += line->dx;
		p1->y += line->sy;
	}
}

void	draw_line(t_fdf *fdf, t_line_data line_data, int j, int i)
{
	t_line	line;
	t_grad	gradient;

	gradient.a = line_data.p1;
	gradient.b = line_data.p2;
	gradient.color_a = line_data.color_a;
	gradient.color_b = line_data.color_b;
	initialize_line(line_data.p1, line_data.p2, &line);
	while (1)
	{
		if (line_data.p1.x >= 0 && line_data.p1.x < fdf->mlx->width
			&& line_data.p1.y >= 0 && line_data.p1.y < fdf->mlx->height)
		{
			mlx_put_pixel(fdf->image, line_data.p1.x, line_data.p1.y,
				fdf->three_d[i][j].color_val);
		}
		if (line_data.p1.x == line_data.p2.x
			&& line_data.p1.y == line_data.p2.y)
			break ;
		update_line(&line_data.p1, &line);
	}
}

int	render_map(t_fdf *fdf)
{
	int	x_dist;
	int	y_dist;

	x_dist = calc_dot_dist_x(fdf);
	y_dist = calc_dot_dist_y(fdf);
	if (x_dist == 0 || y_dist == 0)
	{
		ft_putstr_fd("Error: Invalid map dimensions.\n", 2);
		return (0);
	}
	draw_dots(fdf, x_dist, y_dist);
	return (1);
}
