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
	std::vector<t_point> points;

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
			}

			//DRAW STUFF HERE
		}
	}

	close();

	return (0);
}
