
#include "fdf.h"


#include "fdf.h"

int main(int argc, char **argv)
{
    t_fdf *fdf;

    // Check for correct number of arguments
    if (argc != 2)
    {
        ft_printf("Usage: ./fdf <map_file.fdf>\n");
        return (1);
    }
	// if (argv 2, last char != f && last char - 1 != d && last char - 2 not f && last char - 3 != .)
    // Allocate memory for the main structure
    fdf = malloc(sizeof(t_fdf));
    if (!fdf)
    {
        perror("Error allocating memory for fdf");
        return (1);
    }

    // Allocate memory for the map structure
    fdf->map = malloc(sizeof(t_map));
    if (!fdf->map)
    {
        perror("Error allocating memory for map");
        free(fdf);
        return (1);
    }

    // Parse the .fdf file
    parse_fdf_file(fdf->map, argv[1]);

    // Initialize MLX42
    fdf->mlx = mlx_init(WIDTH, HEIGHT, "FdF", true);
    if (!fdf->mlx)
    {
        ft_printf("Error: Failed to initialize MLX42.\n");
        free(fdf->map);
        free(fdf);
        return (1);
    }

    // Create an image for rendering
    fdf->image = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
    if (!fdf->image)
    {
        ft_printf("Error: Failed to create MLX42 image.\n");
        mlx_terminate(fdf->mlx);
        free(fdf->map);
        free(fdf);
        return (1);
    }

    // Render the map
    render_map(fdf->map, fdf->mlx, fdf->image);

    // Display the image
    mlx_image_to_window(fdf->mlx, fdf->image, 0, 0);

    // Start the MLX42 event loop
    mlx_loop(fdf->mlx);

    // Cleanup
    mlx_delete_image(fdf->mlx, fdf->image);
    mlx_terminate(fdf->mlx);
    free(fdf->map);
    free(fdf);

    return (0);
}