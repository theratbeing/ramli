#include "curses_window.h"
#include <locale.h>
#include <string.h>

int main()
{
	setlocale(LC_ALL, "");
	initscr();
	cbreak();
	noecho();
	refresh();
	
	start_color();
	use_default_colors();
	init_pair(WHITE, COLOR_WHITE, TRANSPARENT);
	init_pair(BLACK, COLOR_BLACK, TRANSPARENT);
	init_pair(BLUE, COLOR_BLUE, TRANSPARENT);
	init_pair(RED, COLOR_RED, TRANSPARENT);
	init_pair(YELLOW, COLOR_YELLOW, TRANSPARENT);
	init_pair(GREEN, COLOR_GREEN, TRANSPARENT);
	init_pair(ORANGE, COLOR_ORANGE, TRANSPARENT);
	init_pair(MAGENTA, COLOR_MAGENTA, TRANSPARENT);
	init_pair(CYAN, COLOR_CYAN, TRANSPARENT);
	
	//int max_row, max_col;
	//getmaxyx(stdscr, max_row, max_col);
	
	/* ========================================== *
	 * Actual program starts here
	 * ========================================== */
	int			key_ch;
	int			select		= 0;
	//int			querent		= 1;
	//int			quesited	= 7;
	int			color_set   = 0;
	unsigned	chart_flags = 0;
	
	char item_label_1[] = "Chart type";
	char item_label_2[] = "Generation method";
	char item_label_3[] = "Correspondence";
	
	char *options_1[] = {"Shield chart", "House chart"};
	char *options_2[] = {"Random", "Figure by figure", "Line by line"};
	char *options_3[] = {"Elemental (modern)", "Elemental (traditional)",
		"Planetary", "Zodiacal (Agrippa)", "Zodiacal (Gerardus)"};
	
	int menu_y   = 3;
	int menu_x   = 3;
	int menu_len = 25;
	
	MenuItem *choices[3];
	WINDOW   *windows[3];
	
	choices[0] = new_menu_item(item_label_1, 2, options_1, menu_len);
	choices[1] = new_menu_item(item_label_2, 3, options_2, menu_len);
	choices[2] = new_menu_item(item_label_3, 5, options_3, menu_len);
	
	for (int i = 0; i < 3; ++i)
	{
		set_item_attr(choices[i], COLOR_PAIR(GREEN));
		windows[i] = window_menu_item(choices[i], i*3+menu_y, menu_x+3);
	}
	
	WINDOW *cursorw = newwin(3*3, 3, menu_y, menu_x);
	keypad(cursorw, TRUE);
	
	while ((key_ch = wgetch(cursorw)) != '\n')
	{
		if (key_ch == KEY_UP)
			--select;
		else if (key_ch == KEY_DOWN)
			++select;
		
		if (select < 0)
			select = 2;
		else if (select > 2)
			select = 0;
		
		if (key_ch == KEY_LEFT)
			shift_menu_item(choices[select], -1);
		else if (key_ch == KEY_RIGHT)
			shift_menu_item(choices[select], 1);
		
		refresh_wmi(windows[select], choices[select]);
		werase(cursorw);
		mvwprintw(cursorw, select*3+1, 0, "(*)");
		wrefresh(cursorw);
	}
	
	/* ========================================== *
	 * Process values from input
	 * ========================================== */
	
	if (choices[0]->value == 0)
		chart_flags |= FLAG_SHIELD;
	else if (choices[0]->value == 1)
		chart_flags |= FLAG_HOUSE;
	
	if (choices[1]->value == 0)
		chart_flags |= FLAG_BY_RANDOM;
	else if (choices[1]->value == 1)
		chart_flags |= FLAG_BY_FIGURE;
	else if (choices[1]->value == 2)
		chart_flags |= FLAG_BY_LINE;
	
	color_set = choices[2]->value;
	
	// no memory leaks
	for (int i = 0; i < 3; ++i)
	{
		delwin(windows[i]);
		del_menu_item(choices[i]);
	}
	
	/* ========================================== *
	 * Chart calculations start here
	 * ========================================== */
	
	int matrix[16][4];
	
	if (chart_flags & FLAG_BY_RANDOM)
	{
		fill_array_random(matrix);
	}
	else if (chart_flags & FLAG_BY_FIGURE)
	{
		unsigned figure_id[4] = {8, 4, 2, 7};
		fill_array_figure(matrix, figure_id);
	}
	else if (chart_flags & FLAG_BY_LINE)
	{
		erase();
		refresh();
		printw("Please randomly type something and press Enter.\n");
		char line[80];
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				printw("%2d out of 16 > ", i*4 + j+1);
				getstr(line);
				matrix[i][j] = (int)strlen(line);
			}
		}
	}
	
	process_array_arithmetics(matrix);
	
	Chart basechart;
	for (int i = 0; i < 16; ++i)
	{
		unsigned id = identify_array(matrix[i]);
		basechart.figures[i] = ptr_figures[id];
	}
	
	erase();
	refresh();
	draw_chart_info(&basechart, color_set, 0, 0);
	
	if (chart_flags & FLAG_SHIELD)
		draw_shield_chart(&basechart, color_set, 0, 33);
	else if (chart_flags & FLAG_HOUSE)
		draw_house_chart(&basechart, color_set, 0, 38);
	
	WINDOW *input_box = newwin(1, 1, 23, 0);
	wgetch(input_box);
	
	endwin();
}
