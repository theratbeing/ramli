#include "curses_window.h"
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void add_min_max(int *target, int val, int i_min, int i_max);
void sub_min_max(int *target, int val, int i_min, int i_max);

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
	
	int max_row, max_col, start_y;
	getmaxyx(stdscr, max_row, max_col);
	
	if (max_row > 24)
		start_y = 1;
	else
		start_y = 0;
	
	paint_ribbon(stdscr, "Ramli v0.1", max_col, A_REVERSE);
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
	char user_query[100] = "Not specified";
	
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
	
	WINDOW *infow = newwin(9, 44, 3, max_col-44-3);
	draw_general_info(infow, user_name, user_query, querent, quesited);
	
	WINDOW *keysw = newwin(11, 74, 13, 3);
	draw_key_info(keysw);
	
	WINDOW *cursorw = newwin(1, 1, 23, 0);
	keypad(cursorw, TRUE);
	curs_set(0);
	
	while ((key_ch = wgetch(cursorw)) != '\n')
	{
		if (key_ch == 'q')
		{
			endwin();
			exit(EXIT_SUCCESS);
		}
		else if (key_ch == KEY_F(2))
		{
			ask_string(user_name, 39, "What is querent's name?", 3, 50, 10, 15);
		}
		else if (key_ch == KEY_F(3))
		{
			ask_string(user_query, 99, "What is the question?", 4, 50, 10, 15);
		}
		else if (key_ch == KEY_F(5))
		{
			ask_house(&querent, "Please enter the house of querent", 3, 15);
		}
		else if (key_ch == KEY_F(6))
		{
			ask_house(&quesited, "Please enter the house of quesited", 3, 15);
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
		
		draw_general_info(infow, user_name, user_query, querent, quesited);
		draw_key_info(keysw);
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
		del_menu_item(choices[i]);
	
	delwin(infow);
	delwin(cursorw);
	
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
		int quarter = max_col / 4;
		int btn_x[16] =
		{
			8, 24, 40, 56,
			8, 24, 40, 56,
			8, 24, 40, 56,
			8, 24, 40, 56,
		};
		
		int btn_y[16] =
		{
			5, 5, 5, 5,
			6, 6, 6, 6,
			7, 7, 7, 7,
			8, 8, 8, 8,
		};
		
		int btnselect = 0;
		
		Button btnar[16];
		for (unsigned i = 0; i < 16; ++i)
		{
			init_button(btnar+i, ptr_figures_alphabetic[i]->name,
						ptr_figures_alphabetic[i]->id, 1, 16, btn_y[i], btn_x[i]);
		}
		
		flip_button(btnar + btnselect);
		
		erase();
		refresh();
		paint_ribbon(stdscr, "Ramli v0.1", max_col, A_REVERSE);
		
		WINDOW *msgbox = newwin(3, max_col, 1, 0);
		box(msgbox, 0, 0);
		mvwprintw(msgbox, 1, (max_col-26)/2, "Please select four figures");
		wrefresh(msgbox);
		
		WINDOW *confbox = newwin(3, max_col, max_row-3, 0);
		box(confbox, 0, 0);
		mvwprintw(confbox, 0, (max_col-16)/2, "Selected figures");
		wrefresh(confbox);
		
		for (int i = 0; i < 16; ++i)
			draw_button(btnar + i);
		
		unsigned figure_id[4];
		keypad(msgbox, TRUE);
		for (int i = 0; i < 4; ++i)
		{
			int quarter_x = i * quarter + ((quarter-5) / 2);
			while ((key_ch = wgetch(msgbox)) != '\n')
			{
				if (key_ch == KEY_RIGHT)
				{
					flip_button(btnar + btnselect);
					draw_button(btnar + btnselect);
					add_min_max(&btnselect, 1, 0, 15);
					flip_button(btnar + btnselect);
				}
				else if (key_ch == KEY_LEFT)
				{
					flip_button(btnar + btnselect);
					draw_button(btnar + btnselect);
					sub_min_max(&btnselect, 1, 0, 15);
					flip_button(btnar + btnselect);
				}
				else if (key_ch == KEY_UP)
				{
					flip_button(btnar + btnselect);
					draw_button(btnar + btnselect);
					sub_min_max(&btnselect, 4, 0, 15);
					flip_button(btnar + btnselect);
				}
				else if (key_ch == KEY_DOWN)
				{
					flip_button(btnar + btnselect);
					draw_button(btnar + btnselect);
					add_min_max(&btnselect, 4, 0, 15);
					flip_button(btnar + btnselect);
				}
				
				draw_button(btnar + btnselect);
				draw_figure_box(ptr_figures_alphabetic[btnselect], color_set, i, max_row-9, quarter_x);
			}
			
			figure_id[i] = btnar[btnselect].value;
			mvwaddstr(confbox, 1, quarter_x, ptr_figures[*(figure_id + i)]->name);
			wrefresh(confbox);
		}
		
		delwin(msgbox);
		delwin(confbox);
		for (int i = 0; i < 16; ++i)
			delwin(btnar[i].pwin);
		
		fill_array_figure(matrix, figure_id);
	}
	else if (chart_flags & FLAG_BY_LINE)
	{
		erase();
		refresh();
		paint_ribbon(stdscr, "Ramli v0.1", max_col, A_REVERSE);
		
		mvprintw(2, 0, "Please randomly type something and press Enter.\n");
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
	basechart.querent  = querent;
	basechart.quesited = quesited;
	for (int i = 0; i < 16; ++i)
	{
		unsigned id = identify_array(matrix[i]);
		basechart.figures[i] = ptr_figures[id];
	}
	
	// Reserve space for analysis
	PNode puncti[15];
	WINDOW *winpuncti = newwin(24, 47, start_y, max_col-47);
	
	House	houses[12];
	bool	occupation;
	VecPair conjunction;
	VecPair mutation;
	VecPair translation;
	
	// Screen output
	erase();
	refresh();
	
	if (max_row > 24)
		paint_ribbon(stdscr, "Ramli v0.1", max_col, A_REVERSE);
	
	draw_chart_info(&basechart, color_set, tstring, start_y, 0);
	WINDOW *input_box = newwin(4, INFOBOX_W, INFOBOX_H + start_y, 0);
	
	if (chart_flags & FLAG_SHIELD)
	{
		init_pnodes(puncti, basechart.figures);
		retrace_pnodes(puncti, 0);
		// winpuncti would overwrite the chart
		draw_via_puncti(winpuncti, puncti, puncti_line);
		draw_shield_chart(&basechart, color_set, start_y, max_col-47);
		draw_key_after(input_box, 's');
	}
	else if (chart_flags & FLAG_HOUSE)
	{
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
		
		draw_house_chart(&basechart, color_set, start_y, max_col-44);
		show_overview(occupation, &conjunction, &mutation, &translation, start_y, max_col-44);
		draw_key_after(input_box, 'h');
	}
	
	int left_info_type = 0;
	keypad(input_box, TRUE);
	
	while ((key_ch = wgetch(input_box)) != 'q')
	{
		if (key_ch == 's')
		{
			char filename[50];
			ask_string(filename, 49, "Please enter file name", 3, 50, 10, 15);
			FILE *fpout = fopen(filename, "w");
			
			if (fpout == NULL)
			{
				WINDOW *errw = newwin(3, 50, 10, 15);
				wattron(errw, COLOR_PAIR(RED));
				box(errw, 0, 0);
				mvwaddstr(errw, 1, 12, "ERROR: Unable to write file");
				wrefresh(errw);
				wgetch(errw);
				delwin(errw);
				continue;
			}
			
			if (chart_flags & FLAG_SHIELD)
				fprintf(fpout, "Shield");
			else
				fprintf(fpout, "House");
			
			fprintf(fpout, " chart generated at %s\n\n", tstring);
			fprintf(fpout, "Name    : %s\nQuestion: %s\n\n", user_name, user_query);
			
			if (chart_flags & FLAG_HOUSE)
				fprintf(fpout, "Querent : %d\nQuesited: %d\n\n", querent, quesited);
			
			for (int i = 0; i < 16; ++i)
			{
				fprintf(fpout, "%2d. %s\n", i+1, basechart.figures[i]->name);
			}
			
			fclose(fpout);
		}
		
		if (key_ch == KEY_RIGHT)
			add_min_max(&color_set, 1, 0, 4);
		else if (key_ch == KEY_LEFT)
			sub_min_max(&color_set, 1, 0, 4);
		
		if (chart_flags & FLAG_HOUSE)
		{
			if (key_ch == '1')
				left_info_type = 1;
			else if (key_ch == '2')
				left_info_type = 2;
			else if (key_ch == '3')
				left_info_type = 3;
			else if (key_ch == '0')
				left_info_type = 0;
			else if (key_ch == KEY_UP)
				sub_min_max(&left_info_type, 1, 0, 3);
			else if (key_ch == KEY_DOWN)
				add_min_max(&left_info_type, 1, 0, 3);
			
			draw_house_chart(&basechart, color_set, start_y, max_col-44);
			show_overview(occupation, &conjunction, &mutation, &translation, start_y, max_col-44);
			
			if (left_info_type == 0)
				draw_chart_info(&basechart, color_set, tstring, start_y, 0);
			else if (left_info_type == 1)
				show_conjunction(&conjunction, start_y, 0);
			else if (left_info_type == 2)
				show_mutation(&mutation, start_y, 0);
			else if (left_info_type == 3)
				show_translation(&translation, start_y, 0);
		}
		
		if (chart_flags & FLAG_SHIELD)
		{
			bool retrace_nodes = false;
			
			if (key_ch == '1')
			{
				puncti_line = 0;
				retrace_nodes = true;
			}
			else if (key_ch == '2')
			{
				puncti_line = 1;
				retrace_nodes = true;
			}
			else if (key_ch == '3')
			{
				puncti_line = 2;
				retrace_nodes = true;
			}
			else if (key_ch == '4')
			{
				puncti_line = 3;
				retrace_nodes = true;
			}
			else if (key_ch == KEY_UP)
			{
				sub_min_max(&puncti_line, 1, 0, 3);
				retrace_nodes = true;
			}
			else if (key_ch == KEY_DOWN)
			{
				add_min_max(&puncti_line, 1, 0, 3);
				retrace_nodes = true;
			}
			
			if (retrace_nodes)
				retrace_pnodes(puncti, puncti_line);
			
			draw_chart_info(&basechart, color_set, tstring, start_y, 0);
			draw_via_puncti(winpuncti, puncti, puncti_line);
			draw_shield_chart(&basechart, color_set, start_y, max_col-47);
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
	
	return EXIT_SUCCESS;
}

void add_min_max(int *target, int val, int i_min, int i_max)
{
	*target += val;
	
	if (*target > i_max)
		*target = *target - i_max - 1 + i_min;
}

void sub_min_max(int *target, int val, int i_min, int i_max)
{
	*target -= val;
	
	if (*target < i_min)
		*target = *target + i_max + 1;
}
