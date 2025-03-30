#ifndef FDF_H
# define FDF_H

# include "MLX42/include/MLX42/MLX42.h"
# include "printf42/ft_printf.h"
# include "libft-42/libft.h"
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
	t_point3d **grid3d;
	t_point2d **grid2d;
	// zoom
	double zoom;
} t_map;

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