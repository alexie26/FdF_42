/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalexan <roalexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:01:32 by roalexan          #+#    #+#             */
/*   Updated: 2025/04/24 17:59:25 by roalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_init(t_fdf *fdf, char *argv)
{
	fdf->zoom = 1.0;
	fdf->z_scale = 1;
	fdf->xrotate = 0;
	fdf->yrotate = 0;
	fdf->zrotate = 0;
	fdf->x_offset = WIDTH / 2;
	fdf->y_offset = HEIGHT / 2;
	fdf->mlx = mlx_init(WIDTH, HEIGHT, argv, true);
	if (!fdf->mlx)
	{
		ft_putstr_fd("Error: Failed to initialize MLX.\n", 2);
		return (free_fdf(fdf), 1);
	}
	fdf->image = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
	if (!fdf->image)
	{
		ft_putstr_fd("Error: Failed to create image.\n", 2);
		return (mlx_terminate(fdf->mlx), free_fdf(fdf), 1);
	}
	return (0);
}

void	clean_map(t_fdf *fdf)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (x < WIDTH)
	{
		while (y < HEIGHT)
		{
			mlx_put_pixel(fdf->image, x, y, 0x22222200);
			y++;
		}
		y = 0;
		x++;
	}
}

void	ft_hook(void *param)
{
	ft_loop_hook(param);
	ft_hook_rotate(param);
	clean_map((t_fdf *)param);
	render_map((t_fdf *)param);
}

int	main(int argc, char *argv[])
{
	t_fdf	*fdf;
	int		fd;

	if (argc != 2)
		handle_error("Usage: ./fdf test_maps/...");
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Error: Unable to open file.\n", 2);
		return (1);
	}
	close(fd);
	fdf = parse(argv[1], -1);
	if (!fdf || !fdf->three_d || fdf->rows <= 0)
	{
		ft_putstr_fd("Error: Failed to parse the map file.\n", 2);
		return (free_fdf(fdf), 1);
	}
	ft_init(fdf, argv[1]);
	mlx_image_to_window(fdf->mlx, fdf->image, 0, 0);
	render_map(fdf);
	mlx_loop_hook(fdf->mlx, &ft_hook, fdf);
	mlx_loop(fdf->mlx);
	return (free_fdf(fdf), 0);
}
