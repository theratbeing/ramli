#include "curses_window.h"
#include <locale.h>
#include <string.h>
#include <time.h>

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
	int			querent		= 1;
	int			quesited	= 7;
	int			puncti_line = 0;
	int			color_set   = 0;
	unsigned	chart_flags = 0;
	
	char user_name[40]  = "Anonymous";
	char user_query[80] = "Not specified";
	
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
	
	int choice_size = 3;
	MenuItem *choices[3];
	
	choices[0] = new_menu_item(item_label_1, 2, options_1);
	choices[1] = new_menu_item(item_label_2, 3, options_2);
	choices[2] = new_menu_item(item_label_3, 5, options_3);
	
	int select = 0;
	select_menu_item(choices[select]);
	
	for (int i = 0; i < choice_size; ++i)
	{
		set_item_window(choices[i], menu_len, COLOR_PAIR(GREEN), i*3+menu_y, menu_x);
		draw_item_window(choices[i]);
	}
	
	WINDOW *cursorw = newwin(1, 1, 23, 1);
	keypad(cursorw, TRUE);
	curs_set(0);
	
	while ((key_ch = wgetch(cursorw)) != '\n')
	{
		if (key_ch == KEY_F(2))
		{
			ask_house(&querent, "Please enter the house of querent", 3, 15);
		}
		else if (key_ch == KEY_F(3))
		{
			ask_house(&quesited, "Please enter the house of quesited", 3, 15);
		}
		else if (key_ch == KEY_F(5))
		{
			ask_string(user_name, 39, "What is querent's name?", 3, 50, 10, 15);
		}
		else if (key_ch == KEY_F(6))
		{
			ask_string(user_query, 79, "What is the question?", 3, 50, 10, 15);
		}
		else if (key_ch == KEY_UP)
		{
			unselect_menu_item(choices[select]);
			--select;
		}
		else if (key_ch == KEY_DOWN)
		{
			unselect_menu_item(choices[select]);
			++select;
		}
		else if (key_ch == KEY_LEFT)
		{
			shift_menu_item(choices[select], -1);
		}
		else if (key_ch == KEY_RIGHT)
		{
			shift_menu_item(choices[select], 1);
		}
		
		if (select < 0)
			select = choice_size - 1;
		else if (select > (choice_size - 1))
			select = 0;
		
		select_menu_item(choices[select]);
		
		for (int i = 0; i < choice_size; ++i)
			draw_item_window(choices[i]);
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
	
	// Get time info before processing the chart
	time_t tstamp	  = time(NULL);
	struct tm *dtdata = localtime(&tstamp); 
	char   tstring[32];
	strftime(tstring, 32, "%F %a %X", dtdata);
	
	// Continue processing
	process_array_arithmetics(matrix);
	
	Chart basechart;
	for (int i = 0; i < 16; ++i)
	{
		unsigned id = identify_array(matrix[i]);
		basechart.figures[i] = ptr_figures[id];
	}
	
	// Reserve space for analysis
	PNode puncti[15];
	WINDOW *winpuncti = newwin(24, 47, 0, 33);
	
	House	houses[12];
	bool	occupation;
	VecPair conjunction;
	VecPair mutation;
	VecPair translation;
	
	// Screen output
	erase();
	refresh();
	draw_chart_info(&basechart, color_set, tstring, 0, 0);
	
	if (chart_flags & FLAG_SHIELD)
	{
		init_pnodes(puncti, basechart.figures);
		retrace_pnodes(puncti, 0);
		// winpuncti would overwrite the chart
		draw_via_puncti(winpuncti, puncti, puncti_line);
		draw_shield_chart(&basechart, color_set, 0, 33);
	}
	else if (chart_flags & FLAG_HOUSE)
	{
		draw_house_chart(&basechart, color_set, 0, 38);
		
		init_houses(houses, basechart.figures);
		House *hquerent  = (houses + querent  - 1);
		House *hquesited = (houses + quesited - 1);
		occupation		 = is_occupied(hquerent, hquesited);
		
		init_vecpair(&conjunction, 4);
		init_vecpair(&mutation, 4);
		init_vecpair(&translation, 4);
		
		check_conjunction(&conjunction, hquerent, hquesited);
		check_translation(&translation, hquerent, hquesited);
		loop_check_mutation(&mutation, houses, hquerent, hquesited);
	}
	
	WINDOW *input_box = newwin(1, 1, 23, 0);
	
	while ((key_ch = wgetch(input_box)) != 'q')
	{
		if (chart_flags & FLAG_HOUSE)
		{
			if (key_ch == '1')
				show_conjunction(&conjunction, 0, 0);
			else if (key_ch == '2')
				show_mutation(&mutation, 0, 0);
			else if (key_ch == '3')
				show_translation(&translation, 0, 0);
			else if (key_ch == '9')
				show_overview(occupation, &conjunction, &mutation, &translation, 0, 0);
			else if (key_ch == '0')
				draw_chart_info(&basechart, color_set, tstring, 0, 0);
		}
		
		if (chart_flags & FLAG_SHIELD)
		{
			bool redraw = false;
			
			if (key_ch == '1')
			{
				puncti_line = 0;
				redraw = true;
			}
			else if (key_ch == '2')
			{
				puncti_line = 1;
				redraw = true;
			}
			else if (key_ch == '3')
			{
				puncti_line = 2;
				redraw = true;
			}
			else if (key_ch == '4')
			{
				puncti_line = 3;
				redraw = true;
			}
			
			if (redraw)
			{
				retrace_pnodes(puncti, puncti_line);
				draw_via_puncti(winpuncti, puncti, puncti_line);
				draw_shield_chart(&basechart, color_set, 0, 33);
			}
		}
	}
	
	// Cleanup
	if (chart_flags & FLAG_HOUSE)
	{
		delete_vecpair(&conjunction);
		delete_vecpair(&mutation);
		delete_vecpair(&translation);
	}
	
	endwin();
}
