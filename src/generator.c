#include "generator.h"

unsigned identify_array(int *ar)
{
	// Returns the enum of figure array
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
