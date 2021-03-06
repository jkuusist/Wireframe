#include "wireframe.h"
#include <stdio.h>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <sstream>

std::vector<std::vector<t_point>> handle_input(int argc, char *args[])
{
	std::vector<std::vector<t_point>> points;
	std::ifstream	input_file;
	float			x = 0.0;
	float			y = 0.0;
	t_point			current;

	if (argc != 2)
		printf("Error\n");

	input_file.open(args[1]);

	if (input_file.is_open())
	{
		for (std::string line; getline(input_file, line);)
		{
			std::vector<t_point> row;

			std::stringstream line_stream(line);

			x = 0;

			while (true)
			{
				float z;

				line_stream >> z;

				if (!line_stream)
					break;

				current = {x, y, -z};

				row.push_back(current);

				x += 1.0;
			}
			points.push_back(row);

			y += 1.0;
		}
	}
	
	input_file.close();

	return (points);
}
