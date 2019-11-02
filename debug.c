#include <stdio.h>
#include "curses_window.h"

int main()
{
	char name[]   = "Test";
	char *label[] = {"Item 1", "Item 2", "Item 3", "Item 4"};
	
	MenuC *menuc = new_menu_child(name, 4, label);
	
	initscr();
	noecho();
	cbreak();
	refresh();
	
	draw_menu_child(menuc, 20, 3, 3);
	
	getch();
	endwin();
	
	del_menu_child(menuc);
	
	return 0;
}
