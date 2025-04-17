/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalexan <roalexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:01:32 by roalexan          #+#    #+#             */
/*   Updated: 2025/04/17 21:28:12 by roalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "fdf.h"

// void leaks(void)
// {
// 	system("leaks fdf");
// }

static char	**expand_lines_array(char **old, int *capacity)
{
	char	**new_array;
	int		i;

	*capacity *= 2;
	new_array = malloc(sizeof(char *) * (*capacity));
	if (!new_array)
		return (NULL);
	i = 0;
	while (old[i])
	{
		new_array[i] = old[i];
		i++;
	}
	new_array[i] = NULL;
	free(old);
	return (new_array);
}

char	**read_file_lines(char *filename, int *out_row)
{
	int		fd;
	char	*line;
	char	**lines;
	int		capacity;
	int		i;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	capacity = 128;
	lines = malloc(sizeof(char *) * capacity);
	if (!lines)
		return (NULL);
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (i >= capacity)
			lines = expand_lines_array(lines, &capacity);
		lines[i++] = line;
	}
	lines[i] = NULL;
	close(fd);
	*out_row = i;
	return (lines);
}

void	display_menu(t_fdf *fdf)
{
	int		x;
	int		y;

	x = 20;
	y = 20;
	mlx_put_string(fdf->mlx, "CONTROLS", x, y);
	mlx_put_string(fdf->mlx, "Colour\t\t\t\t\t\t\t\tc", x, y += 35);
	mlx_put_string(fdf->mlx, "Zoom\t\t\t\t\t\t\t\t\t\t -+", x, y += 20);
	mlx_put_string(fdf->mlx, "Translate\t\t\t\t\tarrow keys", x, y += 20);
	mlx_put_string(fdf->mlx, "Scale z\t\t\t\t\t\t\ts + </>", x, y += 20);
	mlx_put_string(fdf->mlx, "Rotate x\t\t\t\t\t\tx + </>", x, y += 20);
	mlx_put_string(fdf->mlx, "Rotate y\t\t\t\t\t\ty + </>", x, y += 20);
	mlx_put_string(fdf->mlx, "Rotate z\t\t\t\t\t\tz + </>", x, y += 20);
}

// static void malloc_grid(t_fdf *fdf)
// {
// 	int	i;

// 	fdf->three_d = malloc(sizeof(t_3d *) * fdf->rows);
// 	if (!fdf->three_d)
// 		clean_exit(fdf, 0);
// 	i = 0;
// 	while (i < fdf->rows)
// 	{
// 		fdf->three_d[i] = malloc(sizeof(t_3d) * fdf->size);
// 		if (!fdf->three_d[i])
// 			clean_exit(fdf, 1);
// 		i++;
// 	}
// }

void	ft_init(t_fdf *fdf)
{
	fdf->zoom = 1;
	fdf->z_scale = 1;
	fdf->xrotate = 0;
	fdf->yrotate = 0;
	fdf->zrotate = 0;
	fdf->x_offset = WIDTH / 2;
	fdf->y_offset = HEIGHT / 2;
}

void	clean_map(t_fdf *fdf)
{
	for (int x = 0; x < WIDTH; x++)
		for (int y = 0; y < HEIGHT; y++)
			mlx_put_pixel(fdf->image, x, y, 0xff);
}

void	ft_hook(void *param)
{
	ft_loop_hook(param);
	ft_hook_rotate(param);
	clean_map((t_fdf *)param);
	// display_menu((t_fdf *)param);
	render_map((t_fdf *)param);
}

void	free_fdf(t_fdf *fdf)
{
    if (!fdf)
        return;

    // Free the 3D array
    if (fdf->three_d)
        free_tab((void **)fdf->three_d, fdf->rows);

    // Free the 2D array (if applicable)
    if (fdf->two_d)
        free_tab((void **)fdf->two_d, fdf->rows);

    // Free the MLX image
    if (fdf->image)
        mlx_delete_image(fdf->mlx, fdf->image);

    // Terminate MLX
    if (fdf->mlx)
        mlx_terminate(fdf->mlx);

    // Free the main structure
    free(fdf);
}

int	main(int argc, char *argv[])
{
    t_fdf	*fdf;
    int		fd;

    // Check for correct number of arguments
    if (argc != 2)
        handle_error("Usage: ./fdf test_maps/...");

    // Check if the file can be opened
    fd = open(argv[1], O_RDONLY);
    if (fd < 0)
    {
        ft_putstr_fd("Error: Unable to open file.\n", 2);
        return (1);
    }
    close(fd);

    // Parse the file
    fdf = parse(argv[1]);
    if (!fdf || !fdf->three_d || fdf->rows <= 0)
    {
        ft_putstr_fd("Error: Failed to parse the map file.\n", 2);
        free_fdf(fdf); // Free allocated memory
        return (1);
    }

    // Initialize FDF structure
    ft_init(fdf);

    // Initialize MLX
    fdf->mlx = mlx_init(WIDTH, HEIGHT, argv[1], true);
    if (!fdf->mlx)
    {
        ft_putstr_fd("Error: Failed to initialize MLX.\n", 2);
        free_fdf(fdf);
        return (1);
    }

    // Create an image
    fdf->image = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
    if (!fdf->image)
    {
        ft_putstr_fd("Error: Failed to create image.\n", 2);
        mlx_terminate(fdf->mlx);
        free_fdf(fdf);
        return (1);
    }

    // Display the image in the window
    mlx_image_to_window(fdf->mlx, fdf->image, 0, 0);

    // Render the map and set up hooks
    render_map(fdf);
    mlx_loop_hook(fdf->mlx, &ft_hook, fdf);
    mlx_loop(fdf->mlx);

    // Free allocated memory on exit
    free_fdf(fdf);
    return (0);
}
