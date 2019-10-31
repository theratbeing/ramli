#include <stdio.h>
#include "generator.h"
#include "virtues.h"

int main()
{
	int arbsc[16][4];
	
	arbsc[0][0] = 5;
	arbsc[0][1] = 8;
	arbsc[0][2] = 9;
	arbsc[0][3] = 2;
	
	arbsc[1][0] = 6;
	arbsc[1][1] = 8;
	arbsc[1][2] = 3;
	arbsc[1][3] = 2;
	
	arbsc[2][0] = 1;
	arbsc[2][1] = 4;
	arbsc[2][2] = 5;
	arbsc[2][3] = 7;
	
	arbsc[3][0] = 9;
	arbsc[3][1] = 4;
	arbsc[3][2] = 2;
	arbsc[3][3] = 5;
	
	printf("Current array contents:\n");
	for (int i = 0; i < 4; ++i)
	{
		printf("[%d, %d, %d, %d]\n",
			   arbsc[i][0], arbsc[i][1], arbsc[i][2], arbsc[i][3]);
	}
	
	process_array_arithmetics(arbsc);
	
	printf("Current array contents:\n");
	for (int i = 0; i < 16; ++i)
	{
		printf("[%d, %d, %d, %d]\n",
			   arbsc[i][0], arbsc[i][1], arbsc[i][2], arbsc[i][3]);
		
		if (! ((i+1) % 4))
		{
			printf("\n");
		}
	}
}
