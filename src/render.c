/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalexan <roalexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 13:33:51 by roalexan          #+#    #+#             */
/*   Updated: 2025/04/13 16:42:09 by roalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

static	void draw_connect(t_fdf *fdf, int i, int j, t_point p1)
{
	t_point p2;

	if (j + 1 < fdf->three_d[0][0].size)
	{
		p2 = project_isometric(fdf->three_d[i][j + 1], fdf);
		draw_line(fdf, p1, p2, fdf->three_d[i][j].color_val);
	}
	if (i + 1 < fdf->rows)
	{
		p2 = project_isometric(fdf->three_d[i + 1][j], fdf);
		draw_line(fdf, p1, p2, fdf->three_d[i][j].color_val);
	}
}

void	draw_dots(t_fdf *fdf, int dist_x, int dist_y)
{
	int	i;
	int	j;
	t_point	p1;

	i = 0;
	(void)dist_x;
	(void)dist_y;
	while (i < fdf->rows)
	{
		j = 0;
		while (j < fdf->three_d[0][0].size)
		{
			p1 = project_isometric(fdf->three_d[i][j], fdf);
			draw_connect(fdf, i, j, p1);
			j++;
		}
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

void	draw_line(t_fdf *fdf, t_point p1, t_point p2, int color)
{
	t_line	line;

	initialize_line(p1, p2, &line);

	while (1)
	{
		if (p1.x >= 0 && p1.x < fdf->mlx->width && p1.y >= 0 && p1.y < fdf->mlx->height)
		{
			mlx_put_pixel(fdf->image, p1.x, p1.y, color);
			printf("Drawing pixel at (%d, %d)\n", p1.x, p1.y);
		}
		if (p1.x == p2.x && p1.y == p2.y)
			break ;
		update_line(&p1, &line);
	}
}

int		render_map(t_fdf *fdf)
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
	// mlx_clear_image(fdf->image);
	draw_dots(fdf, x_dist, y_dist);
	
	mlx_image_to_window(fdf->mlx, fdf->image, 0, 0);
	return (1);
}

// int	render_map(t_fdf *fdf)
// {
//     int	x_dist;
//     int	y_dist;

//     x_dist = calc_dot_dist_x(fdf);
//     y_dist = calc_dot_dist_y(fdf);

//     if (x_dist == 0 || y_dist == 0)
//     {
//         ft_putstr_fd("Error: Invalid map dimensions.\n", 2);
//         return (0);
//     }

//     // mlx_clear_image(fdf->image);
//     draw_dots(fdf, x_dist, y_dist);
//     mlx_image_to_window(fdf->mlx, fdf->image, 0, 0);
//     return (1);
// }