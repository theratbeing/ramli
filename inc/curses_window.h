#ifndef NEZUMIN_20191031_1813
#define NEZUMIN_20191031_1813

#include "generator.h"
#include <stddef.h>
#include <stdbool.h>
#include <ncurses.h>

#define TRANSPARENT   -1
#define COLOR_ORANGE 208

#define INFOBOX_H 20
#define INFOBOX_W 33

/* ============================================== *
 * Visual representation of geomantic objects
 * ============================================== */

void draw_chart_info(Chart *chart, int mode, const char *dtstr, int y, int x);
void draw_shield_chart(Chart *chart, int mode, int y, int x);
void draw_house_chart(Chart *chart, int mode, int y, int x);

void draw_figure_box(Figure *fgr, int mode, int num, int y, int x);

/* ============================================== *
 * Chart analysis
 * ============================================== */

void draw_via_puncti(WINDOW *pwin, PNode nodes[15], int line);

// Modes of Perfection
void show_overview(bool occu, VecPair *conj, VecPair *muta, VecPair *tran, int y, int x);
void show_conjunction(VecPair *vec, int y, int x);
void show_translation(VecPair *vec, int y, int x);
void show_mutation(VecPair *vec, int y, int x);

/* ============================================== *
 * Program menu/interface
 * ============================================== */

void paint_ribbon(WINDOW *rbnw, char *text, int col, int attr);

typedef struct menu_item
{
	char	*name;
	int		value;
	size_t	size;
	char	**labels;
	bool	selected;
	
	// window data
	int		length;
	int		attr;
	WINDOW	*ptrwin;
} MenuItem;

MenuItem * new_menu_item(char *name, size_t size, char **labels);
void set_item_window(MenuItem *mi, int length, int attr, int y, int x);
void select_menu_item(MenuItem *mi);
void unselect_menu_item(MenuItem *mi);
void shift_menu_item(MenuItem *menui, int diff);
void draw_item_window(MenuItem *mi);
void del_menu_item(MenuItem *menui);

typedef struct menu_button
{
	char	 *label;
	unsigned value;
	bool	 is_selected;
	int		 width;
	WINDOW	 *pwin;
} Button;

void init_button(Button *btn, char *label, unsigned value, int h, int w, int y, int x);
void flip_button(Button *btn);
void draw_button(Button *btn);

void draw_general_info(WINDOW *infow, char *name, char *question, int querent, int quesited);
void draw_key_info(WINDOW *infow);
void draw_key_after(WINDOW *infow, char mode);

void ask_string(char *dest, int len, const char *prompt, int h, int w, int y, int x);
void ask_house(int *dest, const char *prompt, int y, int x);

#endif
