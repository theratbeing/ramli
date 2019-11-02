#include <stdio.h>
#include "curses_window.h"

int main()
{
	char name[]   = "Test";
	char *label[] = {"Item 1", "Item 2", "Item 3", "Item 4"};
	
	MenuItem *menui = new_menu_item(name, 4, label, 15);
	
	initscr();
	noecho();
	cbreak();
	refresh();
	
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
