#ifndef SDL_H
#define SDL_H

int gl_draw();
int sdl_init();
int sdl_exit();
void sdl_pause();

typedef struct
{
	unsigned short n;
	unsigned short u;
} number;

#endif
