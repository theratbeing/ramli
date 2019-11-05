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
	
	PNode *via_puncti[16];
	for (int i = 0; i < 16; ++i)
	{
		via_puncti[i] = new_pnode(basechart.figures[i]);
	}
	link_pnodes_array(via_puncti);
	
	trace_line(via_puncti[14], 0, via_puncti[14]->figure->lines[0]);
	
	for (int i = 0; i < 16; ++i)
	{
		printf("Node number %d has figure %s\n", i+1, via_puncti[i]->figure->name);
		
		if (via_puncti[i]->is_valid)
			printf("\tIt checks out!\n");
		
		if (via_puncti[i]->right)
			printf("\tThe right branch is %s\n", via_puncti[i]->right->figure->name);
		
		if (via_puncti[i]->left)
			printf("\tThe left branch is %s\n", via_puncti[i]->left->figure->name);
	
		printf("\n");
	}
	
	for (int i = 0; i < 16; ++i)
		free(via_puncti[i]);
	
	return 0;
}
