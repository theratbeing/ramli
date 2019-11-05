#include <stdio.h>
#include <stdlib.h>
#include "curses_window.h"

int main()
{
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
	
	printf("%s : %d\n", buffer, num);
	
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
		printf("Opposite: %2d %s\n", wheel[i]->opposite->number, wheel[i]->opposite->figure->name);
		printf("Trine  1: %2d %s\n", wheel[i]->trines[0]->number, wheel[i]->trines[0]->figure->name);
		printf("Trine  2: %2d %s\n", wheel[i]->trines[1]->number, wheel[i]->trines[1]->figure->name);
		printf("Square 1: %2d %s\n", wheel[i]->squares[0]->number, wheel[i]->squares[0]->figure->name);
		printf("Square 2: %2d %s\n", wheel[i]->squares[1]->number, wheel[i]->squares[1]->figure->name);
		printf("Sextile1: %2d %s\n", wheel[i]->sextiles[0]->number, wheel[i]->sextiles[0]->figure->name);
		printf("Sextile2: %2d %s\n", wheel[i]->sextiles[1]->number, wheel[i]->sextiles[1]->figure->name);
		printf("\n");
	}
	
	for (int i = 0; i < 12; ++i)
		free(wheel[i]);
	
	return 0;
}
