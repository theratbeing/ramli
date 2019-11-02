#ifndef NEZUMIN_20191031_1813
#define NEZUMIN_20191031_1813

#include "generator.h"
#include <stddef.h>
#include <ncurses.h>

/* ============================================== *
 * Visual representation of geomantic objects
 * ============================================== */

void draw_chart_info(Chart *chart, int mode, int y, int x);
void draw_shield_chart(Chart *chart, int mode, int y, int x);
void draw_house_chart(Chart *chart, int mode, int y, int x);

void draw_figure_box(Figure *fgr, int mode, int num, int y, int x);


/* ============================================== *
 * Program menu/interface
 * ============================================== */

typedef struct menu_item
{
	char	*name;
	int		value;
	size_t	size;
	char	**labels;
	int		length;
} MenuItem;

MenuItem * new_menu_item(char *name, size_t size, char **labels, int length);
void del_menu_item(MenuItem *menui);

WINDOW * window_menu_item(MenuItem *menui, int y, int x);
void refresh_wmi(WINDOW *win, MenuItem *menui);
void shift_menu_item(MenuItem *menui, int diff);

#endif
