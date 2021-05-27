#include "wireframe.h"

void multiply_point_matrix(t_point *point, matrix44 matrix)
{
	float x, y, z;

	x = point->x * matrix[0][0] + point->y * matrix[1][0] + point->z * matrix[2][0] + matrix[3][0];
	y = point->x * matrix[0][1] + point->y * matrix[1][1] + point->z * matrix[2][1] + matrix[3][1];
	z = point->x * matrix[0][2] + point->y * matrix[1][2] + point->z * matrix[2][2] + matrix[3][2];

	point->x = x;
	point->y = y;
	point->z = z;
}
