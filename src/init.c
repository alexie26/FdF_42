
#include "fdf.h"

void	set_defaults(t_map *map)
{
	map->row = 0;
	map->col = 0;
	map->high_z = INT_MIN;
	map->low_z = INT_MAX;
	map->x_shift = WIDTH / 2;
	map->y_shift = HEIGHT / 2;
	map->space = 1;
	map->zoom = 1;
	map->xrotate = 0;
	map->yrotate = 0;
	map->zrotate = 0;
	map->grid2d = NULL;
	map->grid3d = NULL;
}
