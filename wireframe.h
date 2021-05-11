#ifndef WIREFRAME_H
#define WIREFRAME_H

#include <SDL2/SDL.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

typedef struct	s_point
{
	int x;
	int y;
}				t_point;

void draw_line(t_point start, t_point end, SDL_Renderer *renderer);

#endif
