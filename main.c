#include "curses_window.h"
#include <ncurses.h>
#include <locale.h>
#include <string.h>

#define TRANSPARENT	-1
#define COLOR_ORANGE	208

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
	unsigned	chart_flags = 0;
	
	WINDOW *menu_win = newwin(10, 30, 0, 0);
	
	wprintw(menu_win, "Welcome to Ramli v0.1a\n");
	wprintw(menu_win, "1. Create random chart.\n");
	wprintw(menu_win, "2. Figure by figure.\n");
	wprintw(menu_win, "3. Line by line.\n");
	wrefresh(menu_win);
	
	while((key_ch = wgetch(menu_win)))
	{
		if (key_ch == '1')
		{
			chart_flags |= FLAG_BY_RANDOM;
			break;
		}
		else if (key_ch == '2')
		{
			chart_flags |= FLAG_BY_FIGURE;
			break;
		}
		else if (key_ch == '3')
		{
			chart_flags |= FLAG_BY_LINE;
			break;
		}
	}
	
	werase(menu_win);
	wrefresh(menu_win);
	
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
		printw("Please randomly type something and press Enter .\n");
		char line[80];
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				printw("%d:%d > ", i+1, j+1);
				getstr(line);
				matrix[i][j] = (int)strlen(line);
			}
		}
	}
	
	process_array_arithmetics(matrix);
	
	int color_set = ZODIAC_A;
	Chart basechart;
	for (int i = 0; i < 16; ++i)
	{
		unsigned id = identify_array(matrix[i]);
		basechart.figures[i] = ptr_figures[id];
	}
	
	//draw_chart_info(&basechart, color_set, 0, 0);
	draw_shield_chart(&basechart, color_set, 0, 0);
	
	WINDOW *input_box = newwin(1, 1, 23, 79);
	wgetch(input_box);
	
	endwin();
}
