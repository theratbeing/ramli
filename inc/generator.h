#ifndef NEZUMIN_20191030_1618
#define NEZUMIN_20191030_1618

#include "objects.h"

unsigned	identify_array(int *ar);
void		process_array_arithmetics(int (*ar)[4]);
void		fill_array_random(int (*ar)[4]);
void		fill_array_figure(int (*ar)[4], unsigned *id);

extern const unsigned FLAG_SHIELD;
extern const unsigned FLAG_HOUSE;
extern const unsigned FLAG_AGRIPPA;

extern const unsigned FLAG_BY_RANDOM;
extern const unsigned FLAG_BY_FIGURE;
extern const unsigned FLAG_BY_LINE;

typedef struct chart
{
	unsigned	flags;
	int			querent;
	int			quesited;
	Figure		*figures[16];
} Chart;

#endif
