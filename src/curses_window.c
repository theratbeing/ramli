#include "curses_window.h"
#include <ncurses.h>

void draw_chart_info(Chart *chart, int mode)
{
	WINDOW *winbox = newwin(18, 33, 0, 0);
	box(winbox, 0, 0);
	
	for (int i = 0; i < 16; i++)
	{
		Figure *fgr = chart->figures[i];
		Virtue *vrt = fgr->virtues[mode];
		
		mvwprintw(winbox, i+1, 1, "%2d. %s", i+1, fgr->name);
		wattron(winbox, COLOR_PAIR(vrt->color));
		mvwprintw(winbox, i+1, 21, "%s %s", vrt->symbol, vrt->name);
		wattroff(winbox, COLOR_PAIR(vrt->color));
	}
	
	wrefresh(winbox);
	delwin(winbox);
}
