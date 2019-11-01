#ifndef NEZUMIN_20191030_1756
#define NEZUMIN_20191030_1756

enum color_list
{
	NONE, WHITE, BLACK, BLUE, RED,
	YELLOW, GREEN, ORANGE, MAGENTA, CYAN
};

/* ============================================== *
 * Virtues
 * ============================================== */

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
	enum color_list color;
} Virtue;

extern Virtue *ptr_virtues[25];

/* ============================================== *
 * Figures
 * ============================================== */

enum figure_list
{
	POPULUS, TRISTITIA, ALBUS, F_MAJOR,
	RUBEUS, ACQUISITIO, CONJUNCTIO, CAPUT_D,
	LAETITIA, CARCER, AMISSIO, PUELLA,
	F_MINOR, PUER, CAUDA_D, VIA
};

enum virtue_groups
{
	ELEMENT_M, ELEMENT_T, PLANETARY, ZODIAC_A, ZODIAC_G
};

#define FIGURE_NAME_SIZE   15
#define FIGURE_ABBR_SIZE   11

typedef struct figure
{
	enum	figure_list id;
	char	name[FIGURE_NAME_SIZE];
	char	abbr[FIGURE_ABBR_SIZE];
	int		lines[4];
	Virtue *virtues[5];
} Figure;

extern Figure *ptr_figures[16];
extern Figure *ptr_figures_alphabetic[16];
extern const char *figure_meaning[16];

#endif
