#ifndef NEZUMIN_20191030_1756
#define NEZUMIN_20191030_1756

enum virtue_list
{
	FIRE, AIR, WATER, EARTH,

	SATURN, JUPITER, MARS, SUN, VENUS,
	MERCURY, MOON, NORTH_N, SOUTH_N,

	ARIES, TAURUS, GEMINI, CANCER,
	LEO, VIRGO, LIBRA, SCORPIO,
	SAGITTARIUS, CAPRICORN, AQUARIUS, PISCES, VL_ALL
};

#define VIRTUE_NAME_SIZE   12
#define VIRTUE_ABBR_SIZE    4
#define VIRTUE_SYMBOL_SIZE  5

typedef struct virtue
{
	enum virtue_list id;
	char name[VIRTUE_NAME_SIZE];
	char abbr[VIRTUE_ABBR_SIZE];
	char symbol[VIRTUE_SYMBOL_SIZE];
} Virtue;

extern Virtue *ptr_virtues[25];

#endif
