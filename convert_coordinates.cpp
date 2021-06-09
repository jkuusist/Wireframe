#include "wireframe.h"
#include <cmath>
#include <stdio.h>

std::vector<std::vector<t_int_point>> convert_coordinates(std::vector<std::vector<t_point>> points, t_camera *camera)
{
	std::vector<std::vector<t_int_point>> new_points;
	t_point temp;
	t_int_point new_point;
	float x, y, old_x, old_z;
	matrix44 first_rot(cos(0.785398), 0, -sin(0.785398), 0, 0, 1, 0, 0, sin(0.785398), 0, cos(0.785398), 0, 0, 0, 0, 1);

	matrix44 second_rot(1, 0, 0, 0, 0, cos(0.615472907), sin(0.615472907), 0, 0, -sin(0.615472907), cos(0.615472907), 0, 0, 0, 0, 1);

	matrix44 xy_projection(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1);

	for (int i = 0; i < points.size(); i++)
	{
		std::vector<t_int_point> new_row;

		for (int j = 0; j < points[i].size(); j++)
		{
			temp = {points[i][j].x, points[i][j].y, points[i][j].z};

			temp.x *= camera->zoom;
			temp.y *= camera->zoom;

			multiply_point_matrix(&temp, first_rot);
			multiply_point_matrix(&temp, second_rot);
			multiply_point_matrix(&temp, xy_projection);


			temp.x += (SCREEN_WIDTH / 2);
			temp.y += (SCREEN_HEIGHT / 2);

			new_point = {static_cast<int>(temp.x), static_cast<int>(temp.y), static_cast<int>(temp.z)};
			new_row.push_back(new_point);
		}
		new_points.push_back(new_row);
	}

	return (new_points);
}
