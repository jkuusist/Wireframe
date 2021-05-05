#include <SDL2/SDL.h>
#include <stdio.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

SDL_Window *g_window = NULL;
SDL_Renderer *g_renderer = NULL;

typedef struct	s_point {
	int x;
	int y;
}				t_point;

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

void draw_line(t_point start, t_point end)
{
	int delta_y = end.y - start.y;
	int delta_x = end.x - start.x;
	int x = start.x;
	int y = start.y;

	int p = 2 * delta_y - delta_x;

	SDL_SetRenderDrawColor(g_renderer, 0x00, 0x00, 0x00, 0xFF);

	while (x < end.x)
	{
		if (p >= 0)
		{
			SDL_RenderDrawPoint(g_renderer, x, y);
			y++;
			p = p + 2 *delta_y - 2 * delta_x;
		}
		else
		{
			SDL_RenderDrawPoint(g_renderer, x, y);
			p = p + 2 * delta_y;
		}

		SDL_RenderPresent(g_renderer);

		x++;
	}
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
	t_point start = {0, 10};
	t_point end = {50, 50};

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

			draw_line(start, end);
		}
	}

	close();

	return (0);
}
