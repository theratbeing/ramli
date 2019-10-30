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
	
	for (int i = 0; i < 25; ++i)
	{
		Virtue *member = ptr_virtues[i];
		printf("%2d %s %s\n", member->id, member->symbol, member->name);
	}
}
