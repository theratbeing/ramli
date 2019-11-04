#include "curses_window.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* ============================================== *
 * Visual representation of geomantic objects
 * ============================================== */

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

/* ============================================== *
 * Program menu/interface
 * ============================================== */

MenuItem * new_menu_item(char *name, size_t size, char **labels)
{
	MenuItem *ptr   = malloc(sizeof(MenuItem));
	ptr->name		= name;
	ptr->value		= 0;
	ptr->size		= size;
	ptr->labels		= malloc(size * sizeof(char*));
	ptr->selected	= false;
	
	ptr->length		= 8;
	ptr->attr		= A_NORMAL;
	ptr->ptrwin		= NULL;
	memcpy(ptr->labels, labels, size * sizeof(char*));
	return ptr;
}

void shift_menu_item(MenuItem *menui, int diff)
{
	menui->value += diff;
	int size = (int) menui->size;
	if (menui->value >= size)
		menui->value = 0;
	else if (menui->value < 0)
		menui->value = size - 1;
}

void select_menu_item(MenuItem *mi)
{
	mi->selected = true;
}

void unselect_menu_item(MenuItem *mi)
{
	mi->selected = false;
}

void del_menu_item(MenuItem *menui)
{
	free(menui->labels);
	
	if (menui->ptrwin)
		delwin(menui->ptrwin);
	
	free(menui);
}

void set_item_window(MenuItem *mi, int length, int attr, int y, int x)
{
	mi->attr   = attr;
	mi->length = length;
	
	if (mi->ptrwin)
		delwin(mi->ptrwin);
	
	mi->ptrwin = newwin(3, mi->length+2, y, x);
}

void draw_item_window(MenuItem *mi)
{
	wattron(mi->ptrwin, mi->attr);
	box(mi->ptrwin, 0, 0);
	mvwaddstr(mi->ptrwin, 0, 1, mi->name);
	wattroff(mi->ptrwin, mi->attr);
	
	if (mi->selected)
		wattron(mi->ptrwin, A_STANDOUT);
	
	mvwprintw(mi->ptrwin, 1, 1, "%*s", mi->length, mi->labels[mi->value]);
	
	if (mi->selected)
		wattroff(mi->ptrwin, A_STANDOUT);
	
	wrefresh(mi->ptrwin);
}

/* ============================================== *
 * Dialogues
 * ============================================== */

void ask_string(char *dest, int len, const char *prompt, int h, int w, int y, int x)
{
	int textlen = (int) strlen(prompt);
	if (w < textlen)
		w = textlen;
	
	int mid_x = (w - textlen) / 2;

	WINDOW *dialbox = newwin(h, w, y, x);
	box(dialbox, 0, 0);
	mvwaddstr(dialbox, 0, mid_x, prompt);
	
	curs_set(1);
	echo();
	mvwgetnstr(dialbox, 1, 1, dest, len);
	noecho();
	curs_set(0);
	
	werase(dialbox);
	wrefresh(dialbox);
	delwin(dialbox);
}

void ask_house(int *dest, const char *prompt, int y, int x)
{
	WINDOW *refwin = newwin(14, 50, y, x);
	
	wattron(refwin, COLOR_PAIR(BLUE));
	box(refwin, 0, 0);
	wattroff(refwin, COLOR_PAIR(BLUE));
	
	mvwaddstr(refwin,  1,  1, " 1. The self.");
	mvwaddstr(refwin,  3,  1, " 3. Communication, siblings, neighborhood.");
	mvwaddstr(refwin,  5,  1, " 5. Games, art, children.");
	mvwaddstr(refwin,  7,  1, " 7. Marriage, partnership, rivals.");
	mvwaddstr(refwin,  9,  1, " 9. Higher education, religion, spirituality.");
	mvwaddstr(refwin, 11,  1, "11. Friends, luck, the unknown.");
	
	wattron(refwin, COLOR_PAIR(CYAN));
	mvwaddstr(refwin,  0, 18, "The 12 Houses");
	mvwaddstr(refwin,  2,  1, " 2. Money, moveable wealth.");
	mvwaddstr(refwin,  4,  1, " 4. Land, house, agriculture, parents.");
	mvwaddstr(refwin,  6,  1, " 6. Employee, chores, sickness.");
	mvwaddstr(refwin,  8,  1, " 8. Death, inheritance, debt, occultism.");
	mvwaddstr(refwin, 10,  1, "10. Superiors, government, career.");
	mvwaddstr(refwin, 12,  1, "12. Imprisonment, conspiracy.");
	wattroff(refwin, COLOR_PAIR(CYAN));
	
	wrefresh(refwin);
	
	int textlen = (int) strlen(prompt);
	
	int  mid_x = (50 - textlen) / 2;
	char buffer[3];
	
	WINDOW *dialbox = newwin(3, 50, y+14, x);
	wattron(dialbox, COLOR_PAIR(CYAN));
	box(dialbox, 0, 0);
	mvwaddstr(dialbox, 0, mid_x, prompt);
	wattroff(dialbox, COLOR_PAIR(CYAN));
	curs_set(1);
	echo();

	int  result = 0;
	while (result < 1 || result > 13)
	{
		mvwgetnstr(dialbox, 1, 1, buffer, 2);
		sscanf(buffer, "%d", &result);
	}
	
	*dest = result;
	noecho();
	curs_set(0);
	werase(refwin);
	werase(dialbox);
	wrefresh(refwin);
	wrefresh(dialbox);
	delwin(refwin);
	delwin(dialbox);
}
