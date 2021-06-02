#include "wireframe.h"

#include <stdio.h>

void rotate_x(int *y, int *z, float x_rotation)
{
	int old_y = *y;

	*y = old_y * cos(x_rotation) + *z * sin(x_rotation);
	*z = -old_y * sin(x_rotation) + *z * cos(x_rotation);
}

void rotate_y(int *x, int *z, float y_rotation)
{
	int old_x = *x;

	*x = old_x * cos(y_rotation) + *z * sin(y_rotation);
	*z = -old_x * sin(y_rotation) + *z * cos(y_rotation);
}

void rotate_z(int *x, int *y, float z_rotation)
{
	int old_x = *x;
	int old_y = *y;

	*x = old_x * cos(z_rotation) - old_y * sin(z_rotation);
	*y = old_x * sin(z_rotation) + old_y * cos(z_rotation);
}

void rotate_point(t_int_point *point, t_camera *camera)
{
	rotate_x(&point->y, &point->z, camera->x_rotation);
	rotate_y(&point->x, &point->z, camera->y_rotation);
	rotate_z(&point->x, &point->y, camera->z_rotation);
}
