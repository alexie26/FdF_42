/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalexan <roalexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 20:27:04 by roalexan          #+#    #+#             */
/*   Updated: 2025/04/09 20:55:50 by roalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "printf42/ft_printf.h"
# include "libft-42/libft.h"
# include "getnextline42/get_next_line.h"
# include "MLX42/include/MLX42/MLX42.h"
# include <limits.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>


# define WIDTH 1920
# define HEIGHT 1080
# define MAX_WIDTH 100
# define PI 3.14159265358979323846

typedef struct s_point
{
	int	x;
	int y;
} t_point;

typedef struct	s_3d
{
	int			y;
	int			x;
	int			z;
	int			color_val;
	int			size;
}				t_3d;

typedef struct	s_fdf
{
	char		**map;
	int			rows;
	int			zoom;
	int			z_scale;
	int			x_offset;
	int			y_offset;
	t_3d		**three_d;
	mlx_t		*mlx;
	mlx_image_t	*image;
}				t_fdf;

t_fdf			*parse(char *filename);
// void			pretty_background(t_fdf *fdf);
int	check_for_comma(char *line);
int get_size(char **array);
t_3d	*special_split(t_3d *fdf, char *line, int row);
int get_rows(char *file);
t_fdf	*parse(char *filename);

int	calc_dot_dist_x(t_fdf *fdf);
int	calc_dot_dist_y(t_fdf *fdf);
void	draw_squares(t_fdf *fdf, int x, int y, int color);
void	draw_dots(t_fdf *fdf, int dist_x, int dist_y);
int				render_map(t_fdf *fdf);
void	draw_line(t_fdf *fdf, t_point p1, t_point p2, int color);
t_point project_isometric(t_3d pt, t_fdf *fdf);


void			clean_exit(t_fdf *fdf, int row);
void			ft_loop_hook(void *param);
void key_hook(mlx_key_data_t keydata, void *param);


int main(int argc, char *argv[]);


# endif