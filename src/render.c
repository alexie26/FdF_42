#include "../fdf.h"


void render_map(t_map *map, mlx_t *mlx, mlx_image_t *image)
{
    // Ensure the map and grid2d are valid
    if (!map || !map->grid2d)
        return;

    for (int y = 0; y < map->row; y++)
    {
        for (int x = 0; x < map->col; x++)
        {
            // Draw horizontal lines (to the right)
            if (x + 1 < map->col)
                bresenham(image, (t_point2d){map->grid2d[y][x].x, map->grid2d[y][x].y}, 
                                (t_point3d){map->grid2d[y][x + 1].x, map->grid2d[y][x + 1].y, map->grid2d[y][x + 1].z});

            // Draw vertical lines (downward)
            if (y + 1 < map->row)
                bresenham(image, (t_point2d){map->grid2d[y][x].x, map->grid2d[y][x].y}, 
                                (t_point3d){map->grid2d[y + 1][x].x, map->grid2d[y + 1][x].y, map->grid2d[y + 1][x].z});
        }
    }

    // Display the rendered image in the MLX42 window
    mlx_image_to_window(mlx, image, 0, 0);
}