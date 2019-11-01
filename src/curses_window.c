#include "curses_window.h"
#include <ncurses.h>
#include <string.h>

void draw_chart_info(Chart *chart, int mode, int y, int x)
{
	static const char *mode_label[] =
	{
		"Elements (Modern)", "Elements (Traditional)", "Planetary",
		"Zodiac (Agrippa)", "Zodiac (Gerard of Cremona)"
	};
	
	WINDOW *color_label = newwin(1, 33, y, x);
	
	if (mode == ELEMENT_M || mode == ELEMENT_T)
		wattron(color_label, A_REVERSE | COLOR_PAIR(GREEN));
	else if (mode == PLANETARY)
		wattron(color_label, A_REVERSE | COLOR_PAIR(MAGENTA));
	else if (mode == ZODIAC_A)
		wattron(color_label, A_REVERSE | COLOR_PAIR(YELLOW));
	else
		wattron(color_label, A_REVERSE | COLOR_PAIR(BLUE));
	
	for (int i = 0; i < 33; ++i)
		mvwaddch(color_label, 0, i, ' ');
	
	int mid_x = (33 - strlen(mode_label[mode])) / 2;
	mvwaddstr(color_label, 0, mid_x, mode_label[mode]);
	
	// figure names and correspondence
	WINDOW *winbox = newwin(18, 33, y+1, x);
	box(winbox, 0, 0);
	wrefresh(winbox);	// prevents box outline misallignment
	
	for (int i = 0; i < 16; i++)
	{
		Figure *fgr = chart->figures[i];
		Virtue *vrt = fgr->virtues[mode];
		
		mvwprintw(winbox, i+1, 1, "%2d ", i+1);
		wattron(winbox, COLOR_PAIR(vrt->color));
		mvwprintw(winbox, i+1, 4, "%-14s %s %s", fgr->name, vrt->symbol, vrt->name);
		wattroff(winbox, COLOR_PAIR(vrt->color));
	}
	
	wrefresh(color_label);
	wrefresh(winbox);
	delwin(color_label);
	delwin(winbox);
}

void draw_shield_chart(Chart *chart, int mode, int y, int x)
{
	int xpos[16] =
	{
		// 0,  6, 12, 18, 24, 30, 36, 42,
		42, 36, 30, 24, 18, 12,  6,  0,
		// 3, 15, 27, 39,  9, 33, 21, 42
		39, 27, 15,  3, 33,  9, 21, 42
	};
	
	int ypos[16] =
	{
		0, 0, 0, 0,  0,  0,  0,  0,
		6, 6, 6, 6, 12, 12, 18, 18
	};
	
	for (int i = 0; i < 16; ++i)
	{
		ypos[i] += y;
		xpos[i] += x;
		draw_figure_box(chart->figures[i], mode, i, ypos[i], xpos[i]);
	}
}

void draw_house_chart(Chart *chart, int mode, int y, int x)
{
	int xpos[16] =
	{
		 0,  0,  6, 12, 18, 24,
		24, 24, 18, 12,  6,  0,
		34, 34, 34, 34
	};
	
	int ypos[16] =
	{
		 9, 15, 18, 18, 18, 15,
		 9,  3,  0,  0,  0,  3,
		 0,  6, 12, 18
	};
	
	for (int i = 0; i < 16; ++i)
	{
		ypos[i] += y;
		xpos[i] += x;
		draw_figure_box(chart->figures[i], mode, i, ypos[i], xpos[i]);
	}
}

void draw_figure_box(Figure *fgr, int mode, int num, int y, int x)
{
	WINDOW *win = newwin(6, 5, y, x);
	Virtue *vrt = fgr->virtues[mode];
	
	wattron(win, COLOR_PAIR(vrt->color));
	box(win, 0, 0);
	for (int i = 0; i < 4; i++)
	{
		if (fgr->lines[i])
			mvwprintw(win, i+1, 1, " ● ");
		else
			mvwprintw(win, i+1, 1, "● ●");
	}
	
	/* print labels */
	wattroff(win, COLOR_PAIR(vrt->color));
	mvwprintw(win, 0, 2, "%d", num+1);
	wrefresh(win);
	delwin(win);
}
