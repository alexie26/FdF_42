
#include "fdf.h"

void leaks(void)
{
	system("leaks fdf");
}

int main(int argc, char *argv[])
{
	if (argc != 2)
		return (0);
	t_fdf *fdf = parse(argv[1]);
	fdf->mlx = mlx_init(WIDTH, HEIGHT, argv[1], false);
	fdf->image = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
	mlx_image_to_window(fdf->mlx, fdf->image, 0, 0);
	// pretty_background(fdf);
	render_map(fdf);
	mlx_loop_hook(fdf->mlx, &ft_loop_hook, fdf);
	mlx_loop(fdf->mlx);
	return (0);
}
