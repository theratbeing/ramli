#include "generator.h"

#include <stdlib.h>
#include <time.h>

const unsigned FLAG_SHIELD	  = 1;
const unsigned FLAG_HOUSE	  = 1 << 1;
const unsigned FLAG_AGRIPPA   = 1 << 2;

const unsigned FLAG_BY_RANDOM = 1 << 3;
const unsigned FLAG_BY_FIGURE = 1 << 4;
const unsigned FLAG_BY_LINE   = 1 << 5;

unsigned identify_array(int ar[4])
{
	/* Returns the enum of figure array.
	 * WARNING using this function on numbers other than 0 or 1
	 * may result in segfault */
	unsigned res = 0;
	
	for (int i = 0; i < 4; ++i)
	{
		res = res << 1;
		res |= ar[i];
	}
	
	return res;
}

void process_array_arithmetics(int ar[16][4])
{
	int i, j;
	
	for (i = 0; i < 4; ++i)
	{
		for (j = 0; j < 4; ++j)
		{
			ar[i][j]   = ar[i][j] % 2;	// convert to binary for XOR
			ar[j+4][i] = ar[i][j];		// transposition
		}
	}
	
	for (i = 0; i < 7; ++i)
	{
		for (j = 0; j < 4; ++j)
			ar[i+8][j] = ar[i*2][j] ^ ar[i*2+1][j];
	}
	
	for (i = 0; i < 4; ++i)
		ar[15][i] = ar[14][i] ^ ar[0][i];
}

void fill_array_random(int ar[16][4])
{
	srand((unsigned)time(NULL));
	
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
			ar[i][j] = rand() / (RAND_MAX / 8 + 1);
	}
}

void fill_array_figure(int ar[16][4], unsigned id[4])
{
	for (int i = 0; i < 4; ++i)
	{
		Figure *fsrc = ptr_figures[*(id + i)];
		
		for (int j = 0; j < 4; ++j)
			ar[i][j] = fsrc->lines[j];
	}
}

/* ============================================== *
 * Via Puncti
 * ============================================== */

enum shield_positions
{
	SP_M1, SP_M2, SP_M3, SP_M4, SP_F1, SP_F2, SP_F3, SP_F4,
	SP_N1, SP_N2, SP_N3, SP_N4, SP_W1, SP_W2, SP_JJ, SP_RR
};

void init_pnodes(PNode target[15], Figure *source[16])
{
	for (int i = 0; i < 15; ++i)
	{
		target[i].figure	= source[i];
		target[i].right		= NULL;
		target[i].left		= NULL;
		target[i].is_valid  = false;
	}
	
	for (int i = 0; i < 7; ++i)
	{
		target[SP_N1+i].right = target + (i * 2);
		target[SP_N1+i].left  = target + (i * 2 + 1);
	}
}

void trace_line(PNode *pn, int line, int comp)
{
	if (pn->figure->lines[line] == comp)
		pn->is_valid = true;
	else
		return;
	
	if (pn->right)
		trace_line(pn->right, line, comp);
	
	if (pn->left)
		trace_line(pn->left, line, comp);
}

void retrace_pnodes(PNode ar[15], int line)
{
	for (int i = 0; i < 15; ++i)
	{
		ar[i].is_valid = false;
	}
	
	trace_line((ar + 14), line, ar[14].figure->lines[line]);
}

/* ============================================== *
 * Houses
 * ============================================== */

void init_houses(House target[12], Figure *source[])
{
	for (int i = 0; i < 12; ++i)
	{
		target[i].number = i + 1;
		target[i].figure = source[i];
		
		if (i == 0)
			target[i].prev = target + 11;
		else
			target[i].prev = target + (i - 1);
		
		if (i == 11)
			target[i].next = target;
		else
			target[i].next = target + (i + 1);
		
		// Opposition: 12/2 = 6
		if (i < 6)
			target[i].opposite = target + (i + 6);
		else
			target[i].opposite = target + (i - 6);
		
		// Trine: 12/3 = 4
		if (i < 4)
			target[i].trines[0] = target + (i - 4 + 12);
		else
			target[i].trines[0] = target + (i - 4);
		
		if (i > 7)
			target[i].trines[1] = target + (i + 4 - 12);
		else
			target[i].trines[1] = target + (i + 4);
		
		// Square: 12/4 = 3
		if (i < 3)
			target[i].squares[0] = target + (i - 3 + 12);
		else
			target[i].squares[0] = target + (i - 3);
		
		if (i > 8)
			target[i].squares[1] = target + (i + 3 - 12);
		else
			target[i].squares[1] = target + (i + 3);
		
		// Sextile: 12/6 = 2
		if (i < 2)
			target[i].sextiles[0] = target + (i - 2 + 12);
		else
			target[i].sextiles[0] = target + (i - 2);
		
		if (i > 9)
			target[i].sextiles[1] = target + (i + 2 - 12);
		else
			target[i].sextiles[1] = target + (i + 2);
	}
}

/* ---------------------------------------------- *
 * Vectors
 * ---------------------------------------------- */

void init_vecpair(VecPair *vec, size_t size)
{
	if (vec)
	{
		vec->used	  = 0;
		vec->capacity = size;
		vec->array	  = malloc(size * sizeof(HPair));
	}
}

void append_vecpair(VecPair *vec, HPair pair)
{
	if (vec->used == vec->capacity)
	{
		vec->capacity  *= 2;
		HPair *temp		= realloc(vec->array, vec->capacity * sizeof(HPair));
		if (temp)
		{
			vec->array	= temp;
			temp		= NULL;
		}
	}
	
	vec->array[vec->used] = pair;
	vec->used += 1;
}

void delete_vecpair(VecPair *vec)
{
	free(vec->array);
	vec->array = NULL;
}

/* ---------------------------------------------- *
 * Analysis
 * ---------------------------------------------- */

bool is_occupied(House *querent, House *quesited)
{
	return (querent->figure == quesited->figure
		&& querent->number != quesited->number);
}

void check_conjunction(VecPair *vec, House *querent, House *quesited)
{
	HPair pair;
	
	// These conditions happen independently of each other, hence multiple ifs.
	
	// Quesited moves to querent
	if (querent->next->figure == quesited->figure)
	{
		pair.first  = quesited;
		pair.second = querent->next;
		append_vecpair(vec, pair);
	}
	
	if (querent->prev->figure == quesited->figure)
	{
		pair.first  = quesited;
		pair.second = querent->prev;
		append_vecpair(vec, pair);
	}
	
	// Querent moves to quesited
	if (quesited->next->figure == querent->figure)
	{
		pair.first  = querent;
		pair.second = quesited->next;
		append_vecpair(vec, pair);
	}
	
	if (quesited->prev->figure == querent->figure)
	{
		pair.first  = querent;
		pair.second = quesited->prev;
		append_vecpair(vec, pair);
	}
}

void check_translation(VecPair *vec, House *querent, House *quesited)
{
	HPair pair;
	
	// Compare querent's right side
	if (querent->next->figure == quesited->next->figure
		&& querent->next->figure != quesited->figure
		&& querent->next->figure != querent->figure)
	{
		pair.first  = querent->next;
		pair.second = quesited->next;
		append_vecpair(vec, pair);
	}
	
	if (querent->next->figure == quesited->prev->figure
		&& querent->next->figure != quesited->figure
		&& querent->next->figure != querent->figure)
	{
		pair.first  = querent->next;
		pair.second = quesited->prev;
		append_vecpair(vec, pair);
	}
	
	// Compare querent's left side
	if (querent->prev->figure == quesited->next->figure
		&& querent->prev->figure != quesited->figure
		&& querent->prev->figure != querent->figure)
	{
		pair.first  = querent->prev;
		pair.second = quesited->next;
		append_vecpair(vec, pair);
	}
	
	if (querent->prev->figure == quesited->prev->figure
		&& querent->prev->figure != quesited->figure
		&& querent->prev->figure != querent->figure)
	{
		pair.first  = querent->prev;
		pair.second = quesited->prev;
		append_vecpair(vec, pair);
	}
}

void loop_check_mutation(VecPair *vec, House array[12], House *querent, House *quesited)
{
	HPair pair;
	
	for (int i = 0; i < 12; ++i)
	{
		if (array[i].figure == querent->figure
			&& array[i].number != querent->number)
		{
			if (array[i].prev->figure == quesited->figure)
			{
				pair.first  = array[i].prev;
				pair.second = array + i;
				append_vecpair(vec, pair);
			}
			
			if (array[i].next->figure == quesited->figure)
			{
				pair.first  = array + i;
				pair.second = array[i].next;
				append_vecpair(vec, pair);
			}
		}
	}
}
