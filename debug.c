#include <stdio.h>
#include "generator.h"
#include "virtues.h"

int main()
{
	int array1[] = {3, 7, 5, 4, 2, 1, 1, 9, 5};
	flatten_array(array1, sizeof(array1)/sizeof(int));
	
	for (int i = 0; i < 9; ++i)
	{
		printf("%2d ", array1[i]);
	}
	
	printf("\n");
	
	init_virtues();
	Virtue *fireman = ptr_virtues[FIRE];
	printf("ID: %d %s %s\n", fireman->id, fireman->symbol, fireman->name);
	
}
