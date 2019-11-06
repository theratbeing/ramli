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
		int sa = i * 2;
		int sb = i * 2 + 1;
		
		for (j = 0; j < 4; ++j)
		{
			ar[i+8][j] = ar[sa][j] ^ ar[sb][j];
		}
	}
	
	for (i = 0; i < 4; ++i)
	{
		ar[15][i] = ar[14][i] ^ ar[0][i];
	}
}

void fill_array_random(int ar[16][4])
{
	srand((unsigned)time(NULL));
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			ar[i][j] = rand();
		}
	}
}

void fill_array_figure(int ar[16][4], unsigned id[4])
{
	for (int i = 0; i < 4; ++i)
	{
		Figure *fsrc = ptr_figures[*(id + i)];
		for (int j = 0; j < 4; ++j)
		{
			ar[i][j] = fsrc->lines[j];
		}
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

PNode * new_pnode(Figure *pf)
{
	PNode *ptr = malloc(sizeof(PNode));
	
	if (ptr)
	{
		ptr->figure   = pf;
		ptr->right	  = NULL;
		ptr->left	  = NULL;
		ptr->is_valid = false;
	}
	
	return ptr;
}

void link_pnodes_array(PNode *ar[15])
{
	for (int i = 0; i < 7; ++i)
	{
		ar[SP_N1+i]->right = ar[i*2];
		ar[SP_N1+i]->left  = ar[i*2+1];
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

void retrace_array(PNode *ar[15], int line)
{
	for (int i = 0; i < 15; ++i)
	{
		ar[i]->is_valid = false;
	}
	
	trace_line(ar[14], line, ar[14]->figure->lines[line]);
}

void delete_pnodes(PNode *ar[15])
{
	for (int i = 0; i < 15; ++i)
	{
		free(ar[i]);
		ar[i] = NULL;
	}
}

/* ============================================== *
 * Houses
 * ============================================== */

House * new_house(Figure *pf)
{
	House *ptr  = malloc(sizeof(House));
	
	if (ptr)
	{
		ptr->number = 0;
		ptr->figure = pf;
		ptr->prev   = NULL;
		ptr->next   = NULL;
	}
	
	return ptr;
}

void link_houses(House *ar[12])
{
	for (int i = 0; i < 12; ++i)
	{
		ar[i]->number = i+1;
		
		if (i == 0)
			ar[i]->prev = ar[11];
		else
			ar[i]->prev = ar[i-1];
		
		if (i == 11)
			ar[i]->next = ar[0];
		else
			ar[i]->next = ar[i+1];
		
		// Opposition: 12/2 = 6
		if (i < 6)
			ar[i]->opposite = ar[i+6];
		else
			ar[i]->opposite = ar[i-6];
		
		// Trine: 12/3 = 4
		if (i < 4)
			ar[i]->trines[0] = ar[(i-4)+12];
		else
			ar[i]->trines[0] = ar[i-4];
		
		if (i > 7)
			ar[i]->trines[1] = ar[(i+4)-12];
		else
			ar[i]->trines[1] = ar[i+4];
		
		// Square: 12/4 = 3
		if (i < 3)
			ar[i]->squares[0] = ar[(i-3)+12];
		else
			ar[i]->squares[0] = ar[i-3];
		
		if (i > 8)
			ar[i]->squares[1] = ar[(i+3)-12];
		else
			ar[i]->squares[1] = ar[i+3];
		
		// Sextile: 12/6 = 2
		if (i < 2)
			ar[i]->sextiles[0] = ar[(i-2)+12];
		else
			ar[i]->sextiles[0] = ar[i-2];
		
		if (i > 9)
			ar[i]->sextiles[1] = ar[(i+2)-12];
		else
			ar[i]->sextiles[1] = ar[i+2];
	}
}

void delete_houses(House *ar[12])
{
	for (int i = 0; i < 12; ++i)
	{
		free(ar[i]);
		ar[i] = NULL;
	}
}

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
