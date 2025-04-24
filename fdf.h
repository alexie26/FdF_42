/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalexan <roalexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 20:27:04 by roalexan          #+#    #+#             */
/*   Updated: 2025/04/24 17:51:09 by roalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "MLX42/include/MLX42/MLX42.h"
# include "getnextline42/get_next_line.h"
# include "libft-42/libft.h"
# include "printf42/ft_printf.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>

# define WIDTH 1920
# define HEIGHT 1080
# define MAX_WIDTH 100
# define PI 3.14159265358979323846
# define TEXT_COLOR 0xEAEAEAFF
# define BACKGROUND 0x22222200
# define MENU_BACKGROUND 0x1E1E1EFF
# define COLOR_TEN 0x9e0142ff
# define COLOR_NINE 0xd53e4fff
# define COLOR_EIGHT 0xf46d43ff
# define COLOR_SEVEN 0xfdae61ff
# define COLOR_SIX 0xfee08bff
# define COLOR_FIVE 0xe6f598ff
# define COLOR_FOUR 0xabdda4ff
# define COLOR_THREE 0x66c2a5ff
# define COLOR_TWO 0x3288bdff
# define COLOR_ONE 0x5e4fa2ff

typedef struct s_point
{
	int				x;
	int				y;
}					t_point;

typedef struct s_coords
{
	double			x;
	double			y;
	double			z;
}					t_coords;

typedef struct s_line
{
	double			dx;
	double			dy;
	double			sx;
	double			sy;
	int				err;
}					t_line;

typedef struct s_line_data
{
	t_point			p1;
	t_point			p2;
	int				color_a;
	int				color_b;
}					t_line_data;

typedef struct s_grad
{
	t_point			a;
	t_point			b;
	unsigned int	color_a;
	unsigned int	color_b;
}					t_grad;

typedef struct s_3d
{
	int				y;
	int				x;
	int				z;
	unsigned int	color_val;
	bool			color;
	int				size;
}					t_3d;

typedef struct s_fdf
{
	char			**map;
	int				rows;
	int				zoom;
	int				color;
	int				max_z;
	int				min_z;
	int				z_scale;
	int				x_offset;
	int				y_offset;
	double			xrotate;
	double			yrotate;
	double			zrotate;
	int				size;
	t_3d			**three_d;
	t_point			**two_d;
	mlx_t			*mlx;
	mlx_image_t		*image;
}					t_fdf;

// parsing
// parsing_hex
int					is_upper_hex_char(char c);
int					hex_char_to_int(char c);
unsigned int		hex_to_int(char *hex);
// parse utils
int					check_for_comma(char *line);
int					get_size(char **array);
int					get_rows(char *file);
void				free_split(char **split);
void				get_line_size_malloc(t_fdf *fdf, char *lines,
						int row_count);
// parsing.c
void				initialize_fdf(t_fdf *fdf, char *line, int row);
void				process_file_line(t_fdf *fdf, char *line, int row);
t_fdf				*parse(char *filename, int i);

// parse2
void				handle_comma_case(t_3d *fdf, char *split, int i, int row);
void				handle_no_comma(t_3d *fdf, char *split, int i, int row);
t_3d				*special_split(t_3d *fdf, char *line, int row);

// error utils
void				free_tab(void **tab, size_t len);
void				free_projection(t_fdf *fdf);
void				handle_error(const char *message);
void				clean_exit(t_fdf *fdf, int row);
void				free_fdf(t_fdf *fdf);

// read
char				**read_file_lines(char *filename, int *out_row);
// render
// render_utils
int					calc_dot_dist_x(t_fdf *fdf);
int					calc_dot_dist_y(t_fdf *fdf);
void				draw_squares(t_fdf *fdf, int x, int y, int color);
void				rotate_point(int *x, int *y, t_fdf *fdf);

// render_utils2
void				draw_connect(t_fdf *fdf, int i, int j, int color1);
void				draw_dots(t_fdf *fdf, int dist_x, int dist_y);

// render
void				initialize_line(t_point p1, t_point p2, t_line *line);
void				update_line(t_point *p1, t_line *line);
void				draw_line(t_fdf *fdf, t_line_data line_data, int j, int i);
int					render_map(t_fdf *fdf);
// isometric
t_point				project_isometric(t_3d pt, t_fdf *fdf);
// max_min
int					ft_max(int a, int b);
int					ft_min(int a, int b);

// hooks
void				ft_loop_hook(void *param);
void				ft_hook_rotate(void *param);

// rotate
void				rotate_x(double *y, double *z, double alpha);
void				rotate_y(double *x, double *z, double beta);
void				rotate_z(double *x, double *y, double gamma);
// main.c
int					main(int argc, char *argv[]);

int					ft_init(t_fdf *fdf, char *argv);
void				clean_map(t_fdf *fdf);
void				ft_hook(void *param);

#endif