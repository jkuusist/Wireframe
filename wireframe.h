#ifndef WIREFRAME_H
#define WIREFRAME_H

#include <SDL2/SDL.h>
#include <vector>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

typedef struct	s_point
{
	int x;
	int y;
	int z;
}				t_point;

void								draw_line(t_point start, t_point end, SDL_Renderer *renderer);
std::vector<std::vector<t_point>>	handle_input(int argc, char *args[]);

#endif
