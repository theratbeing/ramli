#include "generator.h"

#include <stdlib.h>
#include <time.h>

const unsigned FLAG_SHIELD	  = 1;
const unsigned FLAG_HOUSE	  = 1 << 1;
const unsigned FLAG_AGRIPPA   = 1 << 2;

const unsigned FLAG_BY_RANDOM = 1 << 3;
const unsigned FLAG_BY_FIGURE = 1 << 4;
const unsigned FLAG_BY_LINE   = 1 << 5;

unsigned identify_array(int *ar)
{
	/* Returns the enum of figure array.
	 * WARNING using this function on numbers other than 0 or 1
	 * may result in segfault */
	unsigned res = 0;
	for (int i = 0; i < 4; ++i)
	{
		res = res << 1;
		res |= ar[i];
	}
	return res;
}

void process_array_arithmetics(int (*ar)[4])
{
	int i, j;
	for (i = 0; i < 4; ++i)
	{
		for (j = 0; j < 4; ++j)
		{
			ar[i][j]   = ar[i][j] % 2;	// convert to binary for XOR
			ar[j+4][i] = ar[i][j];		// transposition
		}
	}
	
	for (i = 0; i < 7; ++i)
	{
		int sa = i * 2;
		int sb = i * 2 + 1;
		
		for (j = 0; j < 4; ++j)
		{
			ar[i+8][j] = ar[sa][j] ^ ar[sb][j];
		}
	}
	
	for (i = 0; i < 4; ++i)
	{
		ar[15][i] = ar[14][i] ^ ar[0][i];
	}
}

void fill_array_random(int (*ar)[4])
{
	srand((unsigned)time(NULL));
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			ar[i][j] = rand();
		}
	}
}

void fill_array_figure(int (*ar)[4], unsigned *id)
{
	for (int i = 0; i < 4; ++i)
	{
		Figure *fsrc = ptr_figures[*(id + i)];
		for (int j = 0; j < 4; ++j)
		{
			ar[i][j] = fsrc->lines[j];
		}
	}
}
