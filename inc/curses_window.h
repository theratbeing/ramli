#ifndef NEZUMIN_20191031_1813
#define NEZUMIN_20191031_1813

#include "generator.h"
#include <stddef.h>
#include <ncurses.h>

#define TRANSPARENT   -1
#define COLOR_ORANGE 208

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
	int		attr;
} MenuItem;

MenuItem * new_menu_item(char *name, size_t size, char **labels, int length);
void set_item_attr(MenuItem *mi, int attr);
void del_menu_item(MenuItem *menui);

WINDOW * window_menu_item(MenuItem *menui, int y, int x);
void refresh_wmi(WINDOW *win, MenuItem *menui);
void shift_menu_item(MenuItem *menui, int diff);

void ask_string(char *dest, int len, const char *prompt, int h, int w, int y, int x);
void ask_house(int *dest, const char *prompt, int h, int w, int y, int x);

#endif
