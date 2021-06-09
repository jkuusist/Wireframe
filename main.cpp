#include "wireframe.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include <vector>

SDL_Window *g_window = NULL;
SDL_Renderer *g_renderer = NULL;

bool init()
{
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		g_window = SDL_CreateWindow("Wireframe", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

		if (g_window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);

			if (g_renderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				SDL_SetRenderDrawColor(g_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
			}
		}
	}

	return (success);
}

void close()
{
	SDL_DestroyRenderer(g_renderer);
	g_renderer = NULL;

	SDL_DestroyWindow(g_window);
	g_window = NULL;

	SDL_Quit();
}


int main(int argc, char *args[])
{
	std::vector<std::vector<t_point>> points;
	std::vector<std::vector<t_int_point>> raster_points;
	t_camera camera = {0, 0, 0, 10};

	points = handle_input(argc, args);

	if (!init())
	{
		printf("Init fail\n");
	}
	else
	{
		bool quit = false;
		SDL_Event e;

		SDL_RenderClear(g_renderer);

		while (!quit)
		{
			while (SDL_PollEvent(&e) != 0)
			{
				if (e.type == SDL_QUIT)
				{
					quit = true;
				}
				else if (e.type == SDL_MOUSEWHEEL)
				{
					camera.zoom += e.wheel.y;

					raster_points.clear();

					raster_points = convert_coordinates(points, &camera);
				}
				else if (e.type == SDL_MOUSEBUTTONDOWN)
				{
					mouse_rotation(&camera);

					for (int i = 0; i < raster_points.size(); i++)
					{
						for (int j = 0; j < raster_points[i].size(); j++)
						{
							rotate_point(&raster_points[i][j], &camera);
						}
					}
				}
			}

			raster_points = convert_coordinates(points, &camera);

			SDL_RenderClear(g_renderer);

			for (int i = 0; i < raster_points.size(); i++)
			{
				for (int j = 0; j < raster_points[i].size(); j++)
				{
					if (j != raster_points[i].size() - 1)
						draw_line(raster_points[i][j], raster_points[i][j + 1], g_renderer);

					if (i < raster_points.size() - 1)
						draw_line(raster_points[i][j], raster_points[i + 1][j], g_renderer);
				}
			}

			SDL_RenderPresent(g_renderer);
		}
	}

	close();

	return (0);
}
