#include "wireframe.h"
#include <SDL2/SDL.h>

void mouse_rotation(t_camera *camera) //, std::vector<std::vector<t_int_point>> points)
{
	SDL_Event e;
	int start_x;
	int start_y;
	int new_x;
	int new_y;
	bool is_pressed = true;

	SDL_GetMouseState(&start_x, &start_y);

	while (is_pressed)
	{
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_MOUSEBUTTONUP)
			{
				is_pressed = false;
			}
			else if (e.type == SDL_MOUSEMOTION)
			{
				SDL_GetMouseState(&new_x, &new_y);

				camera->x_rotation += (new_x - start_x) * 0.001;
				camera->y_rotation += (new_y - start_y) * 0.001;
			}
		}
	}
}
