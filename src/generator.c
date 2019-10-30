#include "generator.h"

void flatten_array(int *ar, size_t len)
{
	for (unsigned i = 0; i < len; ++i)
	{
		ar[i] = ar[i] % 2;
	}
}

// These functions rely on the array being strictly binary: 1 or 0.
void xor_array(int *target, int *src1, int *src2)
{
	for (int i = 0; i < 4; ++i)
	{
		target[i] = src1[i] ^ src2[i];
	}
}

unsigned identify_array(int *ar)
{
	unsigned res = 0;
	for (int i = 0; i < 4; ++i)
	{
		res = res << 1;
		res |= ar[i];
	}
	return res;
}
