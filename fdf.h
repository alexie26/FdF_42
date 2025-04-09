/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalexan <roalexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 20:27:04 by roalexan          #+#    #+#             */
/*   Updated: 2025/04/08 20:18:31 by roalexan         ###   ########.fr       */
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

typedef struct	s_3d
{
	int			x;
	int			y;
	int			z;
	int			color_val;
	int			size;
}				t_3d;

typedef struct	s_fdf
{
	char		**map;
	int			rows;
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


void			clean_exit(t_fdf *fdf, int row);
void			ft_loop_hook(void *param);

int main(int argc, char *argv[]);


# endif