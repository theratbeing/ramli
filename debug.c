#include <stdio.h>
#include <stdlib.h>
#include "curses_window.h"

int main()
{
	/*
	initscr();
	noecho();
	cbreak();
	refresh();
	
	start_color();
	use_default_colors();
	init_pair(WHITE, COLOR_WHITE, TRANSPARENT);
	init_pair(BLACK, COLOR_BLACK, TRANSPARENT);
	init_pair(BLUE, COLOR_BLUE, TRANSPARENT);
	init_pair(RED, COLOR_RED, TRANSPARENT);
	init_pair(YELLOW, COLOR_YELLOW, TRANSPARENT);
	init_pair(GREEN, COLOR_GREEN, TRANSPARENT);
	init_pair(ORANGE, COLOR_ORANGE, TRANSPARENT);
	init_pair(MAGENTA, COLOR_MAGENTA, TRANSPARENT);
	init_pair(CYAN, COLOR_CYAN, TRANSPARENT);
	
	char name[]   = "Test";
	char *label[] = {"Item 1", "Item 2", "Item 3", "Item 4"};
	
	MenuItem *menui = new_menu_item(name, 4, label);
	set_item_window(menui, 15, COLOR_PAIR(GREEN), 3, 3);
	draw_item_window(menui);
	
	char buffer[80];
	int  key = 0;
	int  num;
	while ((key = wgetch(menui->ptrwin)) != 'q')
	{
		if (key == 'j')
			shift_menu_item(menui, -1);
		else if (key == 'l')
			shift_menu_item(menui, 1);
		else if (key == 's')
			ask_string(buffer, 79, "Please enter something", 3, 60, 10, 10);
		else if (key == 'n')
			ask_house(&num, "Enter two digit number", 3, 15);
		
		draw_item_window(menui);
	}
	
	del_menu_item(menui);
	endwin();
	*/
	
	int matrix[16][4];
	unsigned figure_id[4] = {8, 4, 2, 7};
	fill_array_figure(matrix, figure_id);
	process_array_arithmetics(matrix);
	
	Chart basechart;
	for (int i = 0; i < 16; ++i)
	{
		unsigned id = identify_array(matrix[i]);
		basechart.figures[i] = ptr_figures[id];
	}
	
	House *wheel[12];
	for (int i = 0; i < 12; ++i)
	{
		wheel[i] = new_house(basechart.figures[i]);
	}
	link_houses(wheel);
	
	for (int i = 0; i < 12; ++i)
	{
		printf("House %d is %s\n", i+1, wheel[i]->figure->name);
	}
	
	VecPair testvec;
	init_vecpair(&testvec, 4);
	
	printf("testvec has %d of %zu space occupied.\n", testvec.used, testvec.capacity);
	
	for (int i = 0; i < 6; ++i)
	{
		HPair hp = {wheel[i*2], wheel[i*2+1]};
		append_vecpair(&testvec, hp);
		printf("testvec has %d of %zu space occupied.\n", testvec.used, testvec.capacity);
	}
	
	for (unsigned i = 0; i < testvec.used; ++i)
	{
		printf("Item index %d has houses %d and %d.\n",
			   i, testvec.array[i].first->number, testvec.array[i].second->number);
	}
	
	delete_vecpair(&testvec);
	
	for (int i = 0; i < 12; ++i)
		free(wheel[i]);
	
	return 0;
}
