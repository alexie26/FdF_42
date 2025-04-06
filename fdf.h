/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalexan <roalexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 20:27:04 by roalexan          #+#    #+#             */
/*   Updated: 2025/04/06 16:04:19 by roalexan         ###   ########.fr       */
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


# define WIDTH 1980
# define HEIGHT 1080


typedef struct s_point3d
{
	double	x;
	double	y;
	double	z;
	int		mapcolor;
}	t_point3d;

typedef struct s_point2d
{
	double	x;
	double	y;
	double	z;
	int		mapcolor;
}	t_point2d;

typedef	struct s_map
{
	//map
	int		row;
	int		col;
	int		high_z;
	int		low_z;
	//display color and pos
	int		zcolor;
	double	x_shift;
	double	y_shift;
	double	space;
	//rotation
	double	xrotate;
	double	yrotate;
	double	zrotate;
	//grid data
	t_point3d **grid3d; //2D array of 3D points
	t_point2d **grid2d;
	// zoom
	double zoom;
} t_map;

typedef struct s_line_reader
{
	char *mapname;
} t_line_reader;

typedef	struct s_data
{
	t_line_reader line_reader;
	int	fd;
	
}	t_data;

typedef struct s_bresenham
{
	int dx;
	int dy;
	int sx;
	int sy;
	int error[2];
} t_bresenham;

typedef struct s_fdf
{
	mlx_t	*mlx;
	t_map	*map;
	mlx_image_t	*image;
} t_fdf;


//utils
// double	ft_atodbl(char *s);
int	is_valid_number(const char *str);
void	make_upper(unsigned int i, char *c);
int ft_max(int a, int b);
int	ft_min(int a, int b);

//reading
int	file_lenght(const char *filename);
int	valid_file(const char *filename);
int get_map_name(t_data *data, const char *mapname);

//init
void	set_defaults(t_map *map);

//parsing utils
int	parse_color(char *tok, t_point3d *point);
void	process_line(t_map *map, char *line, int row_indx);
//parsing
void	parse_column(t_map *map, char **tab);
void	parse_lines(int **row, char *str);
void	parse_map(t_map *map, char *filename);


//error
void	ft_free_tab(void **tab, size_t len);
void	free_map(t_map *map);
void	handle_error(int status);
void	*ft_free_split(char **strs, int count);
void	free_grid2d(t_map *map, int row_allocated);

//hooks
void	ft_hook(void *param);

//render
void	draw_map(t_fdf *fdf);

//drawing line algorithm
void	project_2d(t_map *map);
void	bresenham(mlx_image_t *image, t_point2d a, t_point3d b);

int	main(int argc, char **argv);

# endif