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
	
	MenuItem *menui = new_menu_item(name, 4, label, 15);
	menui->attr = COLOR_PAIR(GREEN);
	
	WINDOW *wmenui = window_menu_item(menui, 3, 3);
	
	int key = 0;
	while ((key = wgetch(wmenui)) != 'q')
	{
		if (key == 'j')
			shift_menu_item(menui, -1);
		else if (key == 'l')
			shift_menu_item(menui, 1);
		
		refresh_wmi(wmenui, menui);
	}
	
	delwin(wmenui);
	endwin();
	
	del_menu_item(menui);
	
	return 0;
}
