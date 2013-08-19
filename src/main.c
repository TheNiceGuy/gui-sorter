#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "global.h"
#include "sdl.h"

number *sorting_number;
int sorting_size = 20;
int height = 600;
int width  = 1000;
double line_ratio = 0;

int randomize_number();
int bubble_sort();

int main(int argc, char *argv[])
{
	int i;

	for (i = 0; i < argc; ++i)
	{
		if(strcmp(argv[i], "-s") == 0)
		{
			sorting_size = atoi(argv[i+1]);
		}
		else if(strcmp(argv[i], "-h") == 0)
		{
			height = atoi(argv[i+1]);
		}
		else if(strcmp(argv[i], "-w") == 0)
		{
			width = atoi(argv[i+1]);
		}
	}

	sorting_number = malloc(sizeof(number) * sorting_size);
	line_ratio = 2.0 / sorting_size;

	sdl_init();
	randomize_number();

	gl_draw();
	bubble_sort();
	gl_draw();

	sdl_pause();
	sdl_exit();

	free(sorting_number);

	return 0;
}

int randomize_number()
{
	int i = 0;

	srand(time(NULL));

	for(i = 0; i < sorting_size; i++)
	{
		sorting_number[i].u = 0;
		sorting_number[i].n = rand() % 200;
	}

	return 0;
}

int bubble_sort()
{
	int i = 0; /* Index */
	int a = 0; /* Temp Value */
	int b = 0; /* Temp Value */
	int end = 0;

	while(end == 0)
	{
		end = 1;
		for(i = 0; i < sorting_size - 1; i++)
		{
			sorting_number[i].u = 1;
			a = sorting_number[i].n;
			b = sorting_number[i+1].n;

			if(a > b)
			{
				end = 0;

				sorting_number[i].n = b;
				sorting_number[i+1].n = a;
			}
			gl_draw();
			sorting_number[i].u = 0;
		}
	}

	return 0;
}












