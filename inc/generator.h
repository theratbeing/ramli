#ifndef NEZUMIN_20191030_1618
#define NEZUMIN_20191030_1618

#include "objects.h"
#include <stdbool.h>

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

/* ============================================== *
 * Via Puncti
 * ============================================== */

typedef struct puncti_node
{
	Figure				*figure;
	struct puncti_node  *right;
	struct puncti_node  *left;
	bool				is_valid;
} PNode;

PNode * new_pnode(Figure *pf);
void	link_pnodes(PNode *pn, PNode *right, PNode *left);
void	link_pnodes_array(PNode *ar[]);
void	trace_line(PNode *pn, int line, int comp);

/* ============================================== *
 * House chart system and analysis
 * ============================================== */

typedef struct house_node
{
	int					number;
	Figure				*figure;
	struct house_node	*next;
	struct house_node	*prev;
	
	// Aspects
	struct house_node	*opposite;
	struct house_node	*trines[2];
	struct house_node	*squares[2];
	struct house_node	*sextiles[2];
} House;

House * new_house(Figure *pf);
void	link_houses(House *ar[]);

#endif
