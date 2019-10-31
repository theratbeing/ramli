#include "curses_window.h"
#include <ncurses.h>

void draw_chart_info(Chart *chart, int mode)
{
	WINDOW *winbox = newwin(19, 33, 0, 0);
	box(winbox, 0, 0);
	
	const char *mode_label[] =
	{
		"Elements (Modern)", "Elements (Traditional)", "Planetary",
		"Zodiac (Agrippa)", "Zodiac (Gerard of Cremona)"
	};
	
	wattron(winbox, A_UNDERLINE);
	int mid_x = (33 - strlen(mode_label[mode])) / 2;
	mvwaddstr(winbox, 1, mid_x, mode_label[mode]);
	wattroff(winbox, A_UNDERLINE);
	
	for (int i = 0; i < 16; i++)
	{
		Figure *fgr = chart->figures[i];
		Virtue *vrt = fgr->virtues[mode];
		
		mvwprintw(winbox, i+2, 1, "%2d. ", i+1);
		wattron(winbox, COLOR_PAIR(vrt->color));
		mvwaddstr(winbox, i+2, 5, fgr->name);
		//mvwaddwstr(winbox, i+2, 21, vrt->symbol);
		mvwaddstr(winbox, i+2, 23, vrt->name);
		wattroff(winbox, COLOR_PAIR(vrt->color));
	}
	
	wrefresh(winbox);
	delwin(winbox);
}
