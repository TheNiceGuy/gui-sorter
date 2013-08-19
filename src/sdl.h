#ifndef SDL_H
#define SDL_H

#include <stdint.h>

typedef struct
{
	double r;
	double g;
	double b;
} rgb_info;

typedef struct
{
	unsigned short n;
	unsigned short u;
} number;

int gl_draw();
int gl_mix_color(rgb_info *rbg, uint8_t r1, uint8_t r2, uint8_t g1, uint8_t g2, uint8_t b1, uint8_t b2, uint8_t c, uint8_t m);
int sdl_init();
int sdl_exit();
void sdl_pause();

#endif
