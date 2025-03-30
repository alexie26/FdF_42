
#include "fdf.h"

void	bresenham(mlx_image_t *image, t_point2d a, t_point3d b)
{
	int dx;
	int dy;
	int sx;
	int sy;
	int error[2];
	t_point2d current;
	//start initialization point
	current.x = a.x;
	current.y = a.y;
	// diff between points
	dx = abs(b.x - a.x);
	dy = abs(b.y - a.y);

	// step direction for x and y
	if (a.x < b.x)
		sx = 1;
	else
		sx = -1;
	if (a.y < b.y)
		sy = 1;
	else
		sy = -1;
	error[0] = dx - dy;
	while (current.x != b.x || current.y != b.y)
	{
		if ((uint32_t)current.x < image->width && (uint32_t)current.y < image->height)
			mlx_put_pixel(image, current.x, current.y, 0xFFFFFFF);
		error[1] = 2 * error[0];
		if (error[1] > -dy)
		{
			error[0] -= dy;
			current.x += sx;
		}
		if (error[1] < dx)
		{
			error[0] += dx;
			current.y += sy;
		}
	}
}
// When the error term is large in the x-direction, the algorithm moves in the x-direction.
// When the error term is large in the y-direction, the algorithm moves in the y-direction.

