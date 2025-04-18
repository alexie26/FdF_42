/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalexan <roalexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 20:27:04 by roalexan          #+#    #+#             */
/*   Updated: 2025/04/18 18:00:05 by roalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "MLX42/include/MLX42/MLX42.h"
# include "getnextline42/get_next_line.h"
# include "libft-42/libft.h"
# include "printf42/ft_printf.h"
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>

# define WIDTH 1920
# define HEIGHT 1080
# define MAX_WIDTH 100
# define PI 3.14159265358979323846
# define INVALID_MAP		"Map is invalid"
# define FILE_ERROR			"Unable to open file"

typedef struct s_point
{
	int			x;
	int			y;
}				t_point;

typedef struct s_coords
{
	double	x;
	double	y;
	double	z;
}	t_coords;

typedef struct s_line
{
	double		dx;
	double		dy;
	double		sx;
	double		sy;
	int			err;
}				t_line;

typedef struct s_3d
{
	int			y;
	int			x;
	int			z;
	int			color_val;
	int			size;
}				t_3d;

typedef struct s_fdf
{
	char		**map;
	int			rows;
	int			zoom;
	int			z_scale;
	int			x_offset;
	int			y_offset;
	double		xrotate;
	double		yrotate;
	double		zrotate;
	int			size;
	t_3d		**three_d;
	t_point		**two_d;
	mlx_t		*mlx;
	mlx_image_t	*image;
}				t_fdf;

// parse utils
int				check_for_comma(char *line);
int				get_size(char **array);
int				get_rows(char *file);
int				get_line_size(char *line);
void	get_line_size_malloc(t_fdf *fdf, char *lines, int row_count);

// parse
void			handle_comma_case(t_3d *fdf, char *split, int i, int row);
void			handle_no_comma(t_3d *fdf, char *split, int i, int row);
t_3d			*special_split(t_3d *fdf, char *line, int row);
t_fdf			*parse(char *filename, int i);

// render_utils
int				calc_dot_dist_x(t_fdf *fdf);
int				calc_dot_dist_y(t_fdf *fdf);
void			draw_squares(t_fdf *fdf, int x, int y, int color);
void			rotate_point(int *x, int *y, t_fdf *fdf);

// render
void			draw_dots(t_fdf *fdf, int dist_x, int dist_y);
void			initialize_line(t_point p1, t_point p2, t_line *line);
void			update_line(t_point *p1, t_line *line);
void			draw_line(t_fdf *fdf, t_point p1, t_point p2, int color_a, int color_b);
int				render_map(t_fdf *fdf);
void			precompute_projection(t_fdf *fdf);

	// void	draw_line(t_fdf *fdf, t_point p1, t_point p2, int color);

// render2
t_point project_isometric(t_3d pt, t_fdf *fdf);

// error
void			clean_exit(t_fdf *fdf, int row);
void	handle_error(char *msg);
void	free_projection(t_fdf *fdf);


// hooks
void			ft_loop_hook(void *param);
void			ft_hook_rotate(void *param);
void			fdf_zoom(double xdelta, double ydelta, void *param);
void			rotate_x(double *y, double *z, double alpha);
void			rotate_y(double *x, double *z, double beta);
void			rotate_z(double *x, double *y, double gamma);

void			ft_loop_hook(void *param);

void			ft_init(t_fdf *fdf);
void			ft_hook(void *param);
void			free_split(char **split);

//colors
unsigned int create_color(uint8_t r,uint8_t g, uint8_t b, uint8_t a);
unsigned int zcolor(double perc);
void set_zcolor(t_fdf *fdf, int min_z, int max_z);
int radiant(int start, int end, double percentage);
unsigned int get_gradient_color(t_point current, t_point a, t_point b, unsigned int color_a, unsigned int color_b);

void	free_tab(void **tab, size_t len);

#endif