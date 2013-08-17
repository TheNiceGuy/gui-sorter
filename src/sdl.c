#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "global.h"
#include "sdl.h"

extern number *sorting_number;
extern int sorting_size[];
extern int height;
extern int width;
extern double line_ratio;

int gl_draw()
{
	int i = 0;
	float offset = 0;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(-1, -1, 0);
	for(i = 0; i < *sorting_size; i++)
	{
/*		printf("%d %f %f\n", i, offset, sorting_number[i].n / 100.0); */
		printf("%d\n", sorting_number[i].n);
		if(sorting_number[i].u == 1)
		{
			glBegin(GL_QUADS);
				glColor3ub(255, 0, 0);
				glVertex2d(offset             , 0);
				glVertex2d(offset + line_ratio, 0);
				glVertex2d(offset + line_ratio, sorting_number[i].n / 100.0);
				glVertex2d(offset             , sorting_number[i].n / 100.0);
			glEnd();
		}
		else
		{
			glBegin(GL_QUADS);
				glColor3ub(0, 255, 0);
				glVertex2d(offset             , 0);
				glVertex2d(offset + line_ratio, 0);
				glVertex2d(offset + line_ratio, sorting_number[i].n / 100.0);
				glVertex2d(offset             , sorting_number[i].n / 100.0);
			glEnd();
		}

		offset = offset + line_ratio;
	}

	glFlush();
	SDL_GL_SwapBuffers();

	return 0;
}

int sdl_init()
{
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
	{
		printf("Unable to initialize SDL: %s", SDL_GetError());
		return 1;
	}
	if(SDL_SetVideoMode(width, height, 16, SDL_OPENGL) == NULL)
	{
		printf("Can't load video mode: %s\n", SDL_GetError());
		return 1;
	}

	return 0;
}

int sdl_exit()
{
	SDL_Quit();

	return 0;
}

void sdl_pause()
{
	int restart = 1;
	SDL_Event event;

	while(restart)
	{
		SDL_WaitEvent(&event);
		switch(event.type)
		{
			case SDL_QUIT:
				restart = 0;
		}
	}
}
