
#include "fdf.h"

static int window(char *filename)
{
    t_fdf *fdf;
    // Initialize a new fdf structure
    fdf = malloc(sizeof(t_fdf));
    if (!fdf)
    {
        perror("Failed to allocate memory for fdf structure");
        return (1);
    }
    // Create a new window
    fdf->mlx = mlx_init(WIDTH, HEIGHT, filename, false);
    // Create a new image
    fdf->image = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
    if (!fdf->image)
    {
        perror("Failed to create image");
        return (1);
    }
    // Add the image to the window
    mlx_image_to_window(fdf->mlx, fdf->image, 0, 0);
    // Handle events (for example, keypress or window close)
	t_point2d a;
	t_point3d b;
	a.x = 20;
	a.y = 20;
	b.x = 1000;
	b.y = 2000;
	bresenham(fdf->image, a, b);
    mlx_loop(fdf->mlx);
    // Free the allocated memory before exit
    free(fdf);
    return (0);
}

int	main (int argc, char **argv)
{
	if (argc != 2)
    {
        // Display an error message if the wrong number of arguments are passed
        printf("Usage: ./fdf <mapfile.fdf>\n");
        return (1);
    }
    // Initialize the window with the given filename (the map)
    if (window(argv[1]) != 0)
    {
        // If window creation fails, print an error and return
        printf("Failed to create the window.\n");
        return (1);
    }
    return (0);
}
