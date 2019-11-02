#include <stdio.h>
#include "curses_window.h"

int main()
{
	char name[]   = "Test";
	char *label[] = {"Item 1", "Item 2", "Item 3", "Item 4"};
	
	MenuItem *menui = new_menu_item(name, 4, label);
	
	initscr();
	noecho();
	cbreak();
	refresh();
	
	draw_menu_item(menui, 20, 3, 3);
	
	getch();
	endwin();
	
	del_menu_item(menui);
	
	return 0;
}
