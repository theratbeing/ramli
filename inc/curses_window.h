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

typedef struct menu_child
{
	char	*name;
	int		value;
	size_t	size;
	char	**labels;
} MenuC;

MenuC * new_menu_child(char *name, size_t size, char **labels);
void	del_menu_child(MenuC *menuc);
void	shift_menu_child(MenuC *menuc, int diff);
void	draw_menu_child(MenuC *menuc, int len, int y, int x);

#endif
