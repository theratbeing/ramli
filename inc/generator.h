#ifndef NEZUMIN_20191030_1618
#define NEZUMIN_20191030_1618

#include "objects.h"
#include <stdbool.h>
#include <stddef.h>

unsigned	identify_array(int ar[4]);
void		process_array_arithmetics(int ar[16][4]);
void		fill_array_random(int ar[16][4]);
void		fill_array_figure(int ar[16][4], unsigned id[4]);

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

void	init_pnodes(PNode target[15], Figure *source[16]);
void	trace_line(PNode *pn, int line, int comp);
void	retrace_pnodes(PNode ar[15], int line);

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

void	init_houses(House target[12], Figure *source[]);

// Analysis data containers

typedef struct house_pair
{
	House *first;
	House *second;
} HPair;

typedef struct hpair_vector
{
	size_t   capacity;
	unsigned used;
	HPair	 *array;
} VecPair;

void init_vecpair(VecPair *vec, size_t size);
void append_vecpair(VecPair *vec, HPair pair);
void delete_vecpair(VecPair *vec);

// Algorithms

void check_occupation(VecPair *target, House src[12]);

#endif
