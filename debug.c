#include <stdio.h>
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
	return 0;
}
