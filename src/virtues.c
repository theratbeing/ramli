#include "virtues.h"

/* ============================================== *
 * Virtue data
 * ============================================== */

Virtue fire  = { FIRE,  "Fire",  "Fir", "♣", RED };
Virtue air   = { AIR,   "Air",   "Air", "♠", YELLOW };
Virtue water = { WATER, "Water", "Wat", "♥", BLUE };
Virtue earth = { EARTH, "Earth", "Ear", "♦", GREEN };

Virtue saturn  = { SATURN,  "Saturn",	  "Sat", "♄", BLACK };
Virtue jupiter = { JUPITER, "Jupiter",	  "Jup", "♃", BLUE };
Virtue mars    = { MARS,    "Mars",		  "Mar", "♂", RED };
Virtue sun     = { SUN,     "Sun",		  "Sun", "☉", YELLOW };
Virtue venus   = { VENUS,   "Venus",	  "Ven", "♀", GREEN };
Virtue mercury = { MERCURY, "Mercury",	  "Mer", "☿", ORANGE };
Virtue moon    = { MOON,    "Moon",		  "Mon", "☽", MAGENTA };
Virtue north_n = { NORTH_N, "North Node", "Nor", "☊", WHITE };
Virtue south_n = { SOUTH_N, "South Node", "Sou", "☋", WHITE };

Virtue aries	   = { ARIES,		"Aries",		"Ari", "♈", RED };
Virtue taurus	   = { TAURUS,		"Taurus",		"Tau", "♉", GREEN };
Virtue gemini	   = { GEMINI,		"Gemini",		"Gem", "♊", YELLOW };
Virtue cancer	   = { CANCER,		"Cancer",		"Can", "♋", BLUE };
Virtue leo		   = { LEO,			"Leo",			"Leo", "♌", RED };
Virtue virgo	   = { VIRGO,		"Virgo",		"Vir", "♍", GREEN };
Virtue libra	   = { LIBRA,		"Libra",		"Lib", "♎", YELLOW };
Virtue scorpio	   = { SCORPIO,		"Scorpio",		"Sco", "♏", BLUE };
Virtue sagittarius = { SAGITTARIUS, "Sagittarius",  "Sag", "♐", RED };
Virtue capricorn   = { CAPRICORN,	"Capricorn",	"Cap", "♑", GREEN };
Virtue aquarius    = { AQUARIUS,	"Aquarius",		"Aqu", "♒", YELLOW };
Virtue pisces	   = { PISCES,		"Pisces",		"Pis", "♓", BLUE };

Virtue *ptr_virtues[25] =
{
	&fire, &air, &water, &earth,
	
	&saturn, &jupiter, &mars, &sun, &venus,
	&mercury, &moon, &north_n, &south_n,
	
	&aries, &taurus, &gemini, &cancer,
	&leo, &virgo, &libra, &scorpio,
	&sagittarius, &capricorn, &aquarius, &pisces
};

/* ============================================== *
 * Figure data
 * ============================================== */

Figure populus =
{
	POPULUS, "Populus", "Populus", {0, 0, 0, 0},
	{&water, &water, &moon, &cancer, &capricorn}
};

Figure tristitia =
{
	TRISTITIA, "Tristitia", "Tristit.", {0, 0, 0, 1},
	{&earth, &earth, &saturn, &aquarius, &scorpio}
};

Figure albus =
{
	ALBUS, "Albus", "Albus", {0, 0, 1, 0},
	{&water, &water, &mercury, &gemini, &cancer}
};

Figure f_major =
{
	F_MAJOR, "Fortuna Major", "F. Major", {0, 0, 1, 1},
	{&earth, &earth, &sun, &leo, &aquarius}
};

Figure rubeus =
{
	RUBEUS, "Rubeus", "Rubeus", {0, 1, 0, 0},
	{&air, &fire, &mars, &scorpio, &gemini}
};

Figure acquisitio =
{
	ACQUISITIO, "Acquisitio", "Acquisi.", {0, 1, 0, 1},
	{&air, &air, &jupiter, &sagittarius, &aries}
};

Figure conjunctio =
{
	CONJUNCTIO, "Conjunctio", "Conjunc.", {0, 1, 1, 0},
	{&air, &air, &mercury, &virgo, &virgo}
};

Figure caput_d =
{
	CAPUT_D, "Caput Draconis", "Caput D.", {0, 1, 1, 1},
	{&earth, &earth, &north_n, &virgo, &virgo}
};

Figure laetitia =
{
	LAETITIA, "Laetitia", "Laetitia", {1, 0, 0, 0},
	{&fire, &air, &jupiter, &pisces, &taurus}
};

Figure carcer =
{
	CARCER, "Carcer", "Carcer", {1, 0, 0, 1},
	{&earth, &earth, &saturn, &capricorn, &pisces}
};

Figure amissio =
{
	AMISSIO, "Amissio", "Amissio", {1, 0, 1, 0},
	{&fire, &fire, &venus, &taurus, &scorpio}
};

Figure puella =
{
	PUELLA, "Puella", "Puella", {1, 0, 1, 1},
	{&water, &water, &venus, &libra, &libra}
};

Figure f_minor =
{
	F_MINOR, "Fortuna Minor", "F. Minor", {1, 1, 0, 0},
	{&fire, &fire, &sun, &leo, &taurus}
};

Figure puer =
{
	PUER, "Puer", "Puer", {1, 1, 0, 1},
	{&air, &air, &mars, &aries, &gemini}
};

Figure cauda_d =
{
	CAUDA_D, "Cauda Draconis", "Cauda D.", {1, 1, 1, 0},
	{&fire, &fire, &south_n, &sagittarius, &sagittarius}
};

Figure via =
{
	VIA, "Via", "Via", {1, 1, 1, 1},
	{&water, &water, &moon, &cancer, &leo}
};

Figure *ptr_figures[16] =
{
	&populus, &tristitia, &albus, &f_major,
	&rubeus, &acquisitio, &conjunctio, &caput_d,
	&laetitia, &carcer, &amissio, &puella,
	&f_minor, &puer, &cauda_d, &via
};

Figure *ptr_figures_alphabetic[16] =
{
	&acquisitio, &albus, &amissio, &caput_d,
	&carcer, &cauda_d, &conjunctio, &f_major,
	&f_minor, &laetitia, &populus, &puella,
	&puer, &rubeus, &tristitia, &via
};
