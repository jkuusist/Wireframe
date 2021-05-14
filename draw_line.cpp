#include "wireframe.h"
#include <SDL2/SDL.h>
#include <stdlib.h>

void draw_line(t_point start, t_point end, SDL_Renderer *renderer)
{
	int delta_y = abs(end.y - start.y);
	int delta_x = abs(end.x - start.x);
	int x = start.x;
	int y = start.y;
	int x_sign = (end.x > start.x) ? 1 : -1;
	int y_sign = (end.y > start.y) ? 1 : -1;
	int p = 2 * delta_y - delta_x;

	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);

	if (x == end.x && y < end.y)
	{
		while (y < end.y)
		{
			if (p >= 0)
			{
				SDL_RenderDrawPoint(renderer, x, y);
				y += y_sign;
				p = p + 2 * delta_x;
			}
			else
			{
				SDL_RenderDrawPoint(renderer, x, y);
				p = p + 2 * delta_y;
			}
		}
	}
	else if (x == end.x)
	{
		while (y > end.y)
		{
			if (p >= 0)
			{
				SDL_RenderDrawPoint(renderer, x, y);
				y += y_sign;
				p = p + 2 * delta_x;
			}
			else
			{
				SDL_RenderDrawPoint(renderer, x, y);
				p = p + 2 * delta_y;
			}
		}
	}
	else if (x < end.x)
	{
		while (x < end.x)
		{
			if (p >= 0)
			{
				SDL_RenderDrawPoint(renderer, x, y);
				y += y_sign;
				p = p + 2 * delta_x;
			}
			else
			{
				SDL_RenderDrawPoint(renderer, x, y);
				p = p + 2 * delta_y;
			}

			x += x_sign;
		}
	}
	else if (x > end.x)
	{
		while (x > end.x)
		{
			if (p >= 0)
			{
				SDL_RenderDrawPoint(renderer, x, y);
				y += y_sign;
				p = p + 2 * delta_x;
			}
			else
			{
				SDL_RenderDrawPoint(renderer, x, y);
				p = p + 2 * delta_y;
			}

			x += x_sign;
		}
	}
}
