#include "generator.h"
#include <ncurses.h>
#include <locale.h>

#define TRANSPARENT	-1
#define COLOR_ORANGE	208

int main()
{
	setlocale(LC_CTYPE, "");
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
	
	int row, col;
	getmaxyx(stdscr, row, col);
	
	/* ========================================== *
	 * Actual program starts here
	 * ========================================== */
	int			key_ch;
	unsigned	chart_flags = 0;
	
	printw("Welcome to Ramli v0.1a\n");
	printw("1. Create random chart.\n");
	printw("2. Figure by figure.\n");
	printw("3. Line by line.\n");
	
	while(key_ch = getch())
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
	
	endwin();
}
