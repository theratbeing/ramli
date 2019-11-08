#include "curses_window.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* ============================================== *
 * Visual representation of geomantic objects
 * ============================================== */
#define INFOBOX_H 20
#define INFOBOX_W 33

void draw_chart_info(Chart *chart, int mode, const char *dtstr, int y, int x)
{
	static const char *mode_label[] =
	{
		"Elements (Modern)", "Elements (Traditional)", "Planetary",
		"Zodiac (Agrippa)", "Zodiac (Gerard of Cremona)"
	};
	
	WINDOW *winbox = newwin(INFOBOX_H, INFOBOX_W, y, x);
	
	int attributes = A_REVERSE;
	if (mode == ELEMENT_M || mode == ELEMENT_T)
		attributes |= COLOR_PAIR(GREEN);
	else if (mode == PLANETARY)
		attributes |= COLOR_PAIR(MAGENTA);
	else if (mode == ZODIAC_A)
		attributes |= COLOR_PAIR(YELLOW);
	else
		attributes |= COLOR_PAIR(BLUE);
	
	wattron(winbox, attributes);

	// Color ribbons
	for (int i = 0; i < INFOBOX_W; ++i) {
		mvwaddch(winbox, 0, i, ' ');
		mvwaddch(winbox, 19, i, ' ');
	}
	
	int mid_x;
	// Correspondence
	mid_x = (INFOBOX_W - strlen(mode_label[mode])) / 2;
	mvwaddstr(winbox, 0, mid_x, mode_label[mode]);
	
	// Date and time
	mid_x = (INFOBOX_W - strlen(dtstr)) / 2;
	mvwaddstr(winbox, INFOBOX_H-1, mid_x, dtstr);

	wattroff(winbox, attributes);
	
	// Figure names and virtues
	for (int i = 0; i < 16; i++)
	{
		Figure *fgr = chart->figures[i];
		Virtue *vrt = fgr->virtues[mode];
		
		mvwprintw(winbox, i+2, 1, "%2d ", i+1);
		wattron(winbox, COLOR_PAIR(vrt->color));
		mvwprintw(winbox, i+2, 4, "%-14s %s %s", fgr->name, vrt->symbol, vrt->name);
		wattroff(winbox, COLOR_PAIR(vrt->color));
	}
	
	wrefresh(winbox);
	delwin(winbox);
}

int shield_ypos[16] =
{
	0, 0, 0, 0,  0,  0,  0,  0,
	6, 6, 6, 6, 12, 12, 18, 18
};

int shield_xpos[16] =
{
	42, 36, 30, 24, 18, 12,  6,  0,
	39, 27, 15,  3, 33,  9, 21, 42
};

void draw_shield_chart(Chart *chart, int mode, int y, int x)
{
	for (int i = 0; i < 16; ++i)
	{
		int ypos = shield_ypos[i] + y;
		int xpos = shield_xpos[i] + x;
		draw_figure_box(chart->figures[i], mode, i, ypos, xpos);
	}
}

static void draw_line(int y, int x, char type)
{
	WINDOW *lnbox;
	
	if (type == 'l')
	{
		lnbox = newwin(2, 1, y, x+2);
		mvwaddch(lnbox, 0, 0, ACS_VLINE);
		mvwaddch(lnbox, 1, 0, ACS_LLCORNER);
	}
	else if (type == 'r')
	{
		lnbox = newwin(2, 1, y, x+2);
		mvwaddch(lnbox, 0, 0, ACS_VLINE);
		mvwaddch(lnbox, 1, 0, ACS_LRCORNER);
	}
	else if (type == 'L')
	{
		lnbox = newwin(2, 4, y, x+2);
		mvwaddch(lnbox, 0, 0, ACS_VLINE);
		mvwaddch(lnbox, 1, 0, ACS_LLCORNER);
		mvwaddch(lnbox, 1, 1, ACS_HLINE);
		mvwaddch(lnbox, 1, 2, ACS_HLINE);
		mvwaddch(lnbox, 1, 3, ACS_HLINE);
	}
	else if (type == 'R')
	{
		lnbox = newwin(2, 4, y, x-1);
		mvwaddch(lnbox, 0, 3, ACS_VLINE);
		mvwaddch(lnbox, 1, 3, ACS_LRCORNER);
		mvwaddch(lnbox, 1, 2, ACS_HLINE);
		mvwaddch(lnbox, 1, 1, ACS_HLINE);
		mvwaddch(lnbox, 1, 0, ACS_HLINE);
	}
	else if (type == '<')
	{
		lnbox = newwin(2, 10, y, x+2);
		mvwaddch(lnbox, 0, 0, ACS_VLINE);
		mvwaddch(lnbox, 1, 0, ACS_LLCORNER);
		
		for (int i = 1; i < 10; ++i)
			mvwaddch(lnbox, 1, i, ACS_HLINE);
	}
	else if (type == '>')
	{
		lnbox = newwin(2, 10, y, x-7);
		mvwaddch(lnbox, 0, 9, ACS_VLINE);
		mvwaddch(lnbox, 1, 9, ACS_LRCORNER);
		
		for (int i = 0; i < 9; ++i)
			mvwaddch(lnbox, 1, i, ACS_HLINE);
	}
	
	wrefresh(lnbox);
	delwin(lnbox);
}

void draw_via_puncti(PNode nodes[15], int y, int x)
{
	int wy, wx;
	char tptbl[] = "rlrlrlrlRLRL><";
	
	for (int i = 0; i < 14; ++i)
	{
		wy = shield_ypos[i] + y + 6;
		wx = shield_xpos[i] + x;
		
		if (nodes[i].is_valid)
			draw_line(wy, wx, tptbl[i]);
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
 * Modes of Perfection report
 * ============================================== */

void show_overview(bool occu, VecPair *conj, VecPair *muta, VecPair *tran, int y, int x)
{
	WINDOW *overw = newwin(INFOBOX_H, INFOBOX_W, y, x);
	mvwaddstr(overw, 0, 7, "Modes of Perfection");
	
	if (occu)
	{
		mvwprintw(overw, 2, 0, "Occupation found");
	}
	else
	{
		mvwprintw(overw, 2, 0, "No occupation");
	}
	
	if (conj->used == 1)
	{
		mvwprintw(overw, 3, 0, "Found 1 conjunction");
	}
	else if (conj->used > 1)
	{
		mvwprintw(overw, 3, 0, "Found %d conjunctions", conj->used);
	}
	else
	{
		mvwprintw(overw, 3, 0, "No conjunction");
	}
	
	if (muta->used == 1)
	{
		mvwprintw(overw, 4, 0, "Found 1 mutation");
	}
	else if (muta->used > 1)
	{
		mvwprintw(overw, 4, 0, "Found %d mutations", muta->used);
	}
	else
	{
		mvwprintw(overw, 4, 0, "No mutation");
	}
	
	if (tran->used == 1)
	{
		mvwprintw(overw, 5, 0, "Found 1 translation");
	}
	else if (tran->used > 1)
	{
		mvwprintw(overw, 5, 0, "Found %d translations", tran->used);
	}
	else
	{
		mvwprintw(overw, 5, 0, "No translation");
	}
	
	wrefresh(overw);
	delwin(overw);
}

void show_conjunction(VecPair *vec, int y, int x)
{
	WINDOW *repw = newwin(INFOBOX_H, INFOBOX_W, y, x);
	mvwaddstr(repw, 0, 11, "Conjunctions");
	
	if (vec->used)
	{
		for (unsigned i = 0; i < vec->used; ++i)
		{
			mvwprintw(repw, i+2, 1, "%2d %s moves to %2d %s",
				vec->array[i].first->number,  vec->array[i].first->figure->abbr,
				vec->array[i].second->number, vec->array[i].second->figure->abbr);
		}
	}
	else
	{
		mvwprintw(repw, 2, 0, "No conjunction");
	}
	
	wrefresh(repw);
	delwin(repw);
}

void show_translation(VecPair *vec, int y, int x)
{
	WINDOW *repw = newwin(INFOBOX_H, INFOBOX_W, y, x);
	mvwaddstr(repw, 0, 10, "Translations");
	
	if (vec->used)
	{
		for (unsigned i = 0; i < vec->used; ++i)
		{
			mvwprintw(repw, i+2, 1, "%2d %s moves to %2d %s",
				vec->array[i].first->number,  vec->array[i].first->figure->abbr,
				vec->array[i].second->number, vec->array[i].second->figure->abbr);
		}
	}
	else
	{
		mvwprintw(repw, 2, 0, "No translation");
	}
	
	wrefresh(repw);
	delwin(repw);
}

void show_mutation(VecPair *vec, int y, int x)
{
	WINDOW *repw = newwin(INFOBOX_H, INFOBOX_W, y, x);
	mvwaddstr(repw, 0, 12, "Mutations");
	
	if (vec->used)
	{
		for (unsigned i = 0; i < vec->used; ++i)
		{
			mvwprintw(repw, i+2, 0, "%2d %s and %2d %s",
				vec->array[i].first->number,  vec->array[i].first->figure->abbr,
				vec->array[i].second->number, vec->array[i].second->figure->abbr);
		}
	}
	else
	{
		mvwprintw(repw, 2, 0, "No mutation");
	}
	
	wrefresh(repw);
	delwin(repw);
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
