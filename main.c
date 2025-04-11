
#include "fdf.h"

// void leaks(void)
// {
// 	system("leaks fdf");
// }

void	ft_hook(void *param)
{
	ft_loop_hook(param);
	// ft_scrollhook(param);
	ft_hook_rotate(param); 
	render_map((t_fdf *)param);
}

int main(int argc, char *argv[])
{
	if (argc != 2)
		return (0);
	t_fdf *fdf = parse(argv[1]);
	fdf->mlx = mlx_init(WIDTH, HEIGHT, argv[1], true);
	fdf->image = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
	mlx_image_to_window(fdf->mlx, fdf->image, 0, 0);
	// pretty_background(fdf);
	render_map(fdf);
	mlx_scroll_hook(fdf->mlx, &fdf_scrollhook, fdf);
	mlx_loop_hook(fdf->mlx, &ft_hook, fdf);  
	mlx_loop(fdf->mlx);
	return (0);
}
