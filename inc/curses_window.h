#ifndef NEZUMIN_20191031_1813
#define NEZUMIN_20191031_1813

/* WARNING
 * The preprocessor directive bellow MUST be declared
 * before you include ncurses. Otherwise the wide-char
 * functions will not be loaded!
 */

#define _XOPEN_SOURCE_EXTENDED

#include "generator.h"

void draw_chart_info(Chart *chart, int mode);

#endif
