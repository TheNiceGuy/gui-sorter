#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "global.h"
#include "sdl.h"

extern number *sorting_number;
extern int sorting_size;
extern int height;
extern int width;
extern double line_ratio;

static SDL_Surface *screen = NULL;

int gl_draw()
{
	int i = 0;
	float offset = 0;
	rgb_info rgb;

	rgb.r = 0;
	rgb.g = 0;
	rgb.b = 0;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(-1, -1, 0);
	for(i = 0; i < sorting_size; i++)
	{
		if(sorting_number[i].u == 1)
		{
			gl_mix_color(&rgb,
				     GRADIENT_3_R, GRADIENT_1_R,
				     GRADIENT_3_G, GRADIENT_1_G,
				     GRADIENT_3_B, GRADIENT_1_B,
				     (int)sorting_number[i].n, 200);
			glBegin(GL_QUADS);
				glColor3ub(GRADIENT_3_R, GRADIENT_3_G, GRADIENT_3_B);
				glVertex2d(offset             , 0);
				glVertex2d(offset + line_ratio, 0);
				glColor3ub(rgb.r, rgb.g, rgb.b);
				glVertex2d(offset + line_ratio, sorting_number[i].n / 100.0);
				glVertex2d(offset             , sorting_number[i].n / 100.0);
			glEnd();
		}
		else
		{
			gl_mix_color(&rgb,
				     GRADIENT_3_R, GRADIENT_2_R,
				     GRADIENT_3_G, GRADIENT_2_G,
				     GRADIENT_3_B, GRADIENT_2_B,
				     (int)sorting_number[i].n, 200);
			glBegin(GL_QUADS);
				glColor3ub(GRADIENT_3_R, GRADIENT_3_G, GRADIENT_3_B);
				glVertex2d(offset             , 0);
				glVertex2d(offset + line_ratio, 0);
				glColor3ub(rgb.r, rgb.g, rgb.b);
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

int gl_mix_color(rgb_info *rbg, uint8_t r1, uint8_t r2, uint8_t g1, uint8_t g2, uint8_t b1, uint8_t b2, uint8_t c, uint8_t m)
{
	uint8_t c1 = (c * 100) / m;
	uint8_t c2 = 100 - c1;

	printf("%d %d\n", c1, c2);

	rbg->r = (r1 * (c2 / 100.0)) + (r2 * (c1 / 100.0));
	rbg->g = (g1 * (c2 / 100.0)) + (g2 * (c1 / 100.0));
	rbg->b = (b1 * (c2 / 100.0)) + (b2 * (c1 / 100.0));	

	return 1; 
}

int sdl_init()
{
	if(SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		printf("Unable to initialize SDL: %s", SDL_GetError());
		return 1;
	}
	screen = SDL_SetVideoMode(width, height, 16, SDL_OPENGL);
	if(screen == NULL)
	{
		printf("Can't load video mode: %s\n", SDL_GetError());
		return 1;
	}

	return 0;
}

int sdl_exit()
{
	SDL_FreeSurface(screen);
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
