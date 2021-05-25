#include "wireframe.h"
#include <cmath>
#include <stdio.h>

std::vector<std::vector<t_int_point>> convert_coordinates(std::vector<std::vector<t_point>> points)
{
	std::vector<std::vector<t_int_point>> new_points;
	t_int_point new_point;
	float x, y, old_x, old_z;

	for (int i = 0; i < points.size(); i++)
	{
		std::vector<t_int_point> new_row;

		for (int j = 0; j < points[i].size(); j++)
		{

			old_x = points[i][j].x;
			old_z = points[i][j].z;

			x = (old_x - old_z) * cos(0.523599);
			y = -points[i][j].y + (old_x + old_z) * sin(0.523599);

			x += (SCREEN_WIDTH / 2);
			y += (SCREEN_HEIGHT / 2);

			new_point = {static_cast<int>(x), static_cast<int>(y), 0};

			new_row.push_back(new_point);
		}
		new_points.push_back(new_row);
	}

	return (new_points);
}
