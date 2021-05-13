#include "wireframe.h"
#include <stdio.h>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <sstream>

std::vector<t_point> handle_input(int argc, char *args[])
{
	std::vector<t_point> points;
	std::ifstream	input_file;
	int				x = 0;
	int				y = 0;
	t_point			current;

	if (argc != 2)
		printf("Error\n");

	input_file.open(args[1]);

	if (input_file.is_open())
	{
		for (std::string line; getline(input_file, line);)
		{
			std::stringstream line_stream(line);

			x = 0;

			while (true)
			{
				int z;

				line_stream >> z;

				if (!line_stream)
					break;

				current = {x, y, z};

				points.push_back(current);

				x++;
			}

			y++;
		}
	}
	
	input_file.close();

	return (points);
}
