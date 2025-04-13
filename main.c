
#include "fdf.h"

// void leaks(void)
// {
// 	system("leaks fdf");
// }

void	ft_init(t_fdf *fdf)
{
	t_point	top_left;
	t_point	bottom_right;

	fdf->zoom = 6;
	fdf->z_scale = 1;

	fdf->xrotate = 0;
	fdf->yrotate = 0;
	fdf->zrotate = 0;

	top_left = project_isometric(fdf->three_d[0][0], fdf);
	bottom_right = project_isometric(fdf->three_d[fdf->rows - 1][fdf->three_d[0][0].size - 1], fdf);

	fdf->x_offset = WIDTH / 2;
	fdf->y_offset = HEIGHT / 2;
}

void	ft_hook(void *param)
{
	ft_loop_hook(param);
	// ft_scrollhook(param);
	// ft_hook_rotate(param); 
	render_map((t_fdf *)param);
}

// int main(int argc, char *argv[])
// {
// 	if (argc != 2)
// 		return (0);
// 	t_fdf *fdf = parse(argv[1]);
// 	fdf->mlx = mlx_init(WIDTH, HEIGHT, argv[1], true);
// 	fdf->image = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
// 	mlx_image_to_window(fdf->mlx, fdf->image, 0, 0);
// 	// pretty_background(fdf);
// 	render_map(fdf);
// 	// mlx_scroll_hook(fdf->mlx, &fdf_scrollhook, fdf);
// 	mlx_loop_hook(fdf->mlx, &ft_hook, fdf);  
// 	mlx_loop(fdf->mlx);
// 	return (0);
// }


int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        ft_putstr_fd("Usage: ./fdf <map_file>\n", 2);
        return (1);
    }

    t_fdf *fdf = parse(argv[1]);
	ft_init(fdf);
    if (!fdf || !fdf->three_d || fdf->rows <= 0)
    {
        ft_putstr_fd("Error: Failed to parse the map file.\n", 2);
        return (1);
    }

    fdf->mlx = mlx_init(WIDTH, HEIGHT, argv[1], true);
    if (!fdf->mlx)
    {
        ft_putstr_fd("Error: Failed to initialize MLX.\n", 2);
        return (1);
    }

    fdf->image = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
    if (!fdf->image)
    {
        ft_putstr_fd("Error: Failed to create image.\n", 2);
        mlx_terminate(fdf->mlx);
        return (1);
    }

    mlx_image_to_window(fdf->mlx, fdf->image, 0, 0);
    render_map(fdf);
    mlx_loop_hook(fdf->mlx, &ft_hook, fdf);  
    mlx_loop(fdf->mlx);
    return (0);
}
