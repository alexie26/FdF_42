
#include "fdf.h"

static int window(t_map *map, char *filename)
{
	t_fdf *fdf;

	fdf = malloc(sizeof(t_fdf));
	if (!fdf)
	{
		perror("Failed to allocate memory for fdf structure");
		return (1);
	}
	fdf->map = map;

	// Init MLX window
	fdf->mlx = mlx_init(WIDTH, HEIGHT, filename, false);
	if (!fdf->mlx)
	{
		perror("Failed to initialize MLX");
		return (1);
	}
	fdf->image = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
	mlx_put_pixel(fdf->image, WIDTH / 2, HEIGHT / 2, 0xFFFFFFFF);
	if (!fdf->image)
	{
		perror("Failed to create image");
		return (1);
	}
	mlx_image_to_window(fdf->mlx, fdf->image, 0, 0);
	// Project 3D points to 2D
	project_2d(fdf->map);
	// Draw the full wireframe
	draw_map(fdf);
	// Start MLX event loop
	mlx_loop(fdf->mlx);

	free(fdf);
	return (0);
}

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("Usage: ./fdf <mapfile.fdf>\n");
		return (1);
	}
	t_map map;

	set_defaults(&map);
	parse_map(&map, argv[1]); // this allocates grid2d too
	if (window(&map, argv[1]) != 0)
	{
		printf("Failed to create the window.\n");
		return (1);
	}
	return (0);
}
