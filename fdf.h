#ifndef FDF_H
# define FDF_H

# include "MLX42/include/MLX42/MLX42.h"
# include "printf42/ft_printf.h"
# include "libft-42/libft.h"
# include "getnextline42/get_next_line.h"
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

typedef	struct s_data
{
	t_line_reader line_reader;
	int	fd;
	
}	t_data;

typedef struct s_line_reader
{
	char *mapname;
} t_line_reader;

typedef struct s_fdf
{
	mlx_t	*mlx;
	t_map	*map;
	mlx_image_t	*image;
} t_fdf;


//utils
double	ft_atodbl(char *s);
int	is_valid_number(const char *str);
int	valid_file(const char *filename);

//drawing line algorithm

# endif