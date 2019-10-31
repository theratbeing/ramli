#include "virtues.h"

Virtue fire  = { FIRE,  "Fire",  "Fir", "♣" };
Virtue air   = { AIR,   "Air",   "Air", "♠" };
Virtue water = { WATER, "Water", "Wat", "♥" };
Virtue earth = { EARTH, "Earth", "Ear", "♦" };

Virtue saturn  = { SATURN,  "Saturn",	  "Sat", "♄" };
Virtue jupiter = { JUPITER, "Jupiter",	  "Jup", "♃" };
Virtue mars    = { MARS,    "Mars",		  "Mar", "♂" };
Virtue sun     = { SUN,     "Sun",		  "Sun", "☉" };
Virtue venus   = { VENUS,   "Venus",	  "Ven", "♀" };
Virtue mercury = { MERCURY, "Mercury",	  "Mer", "☿" };
Virtue moon    = { MOON,    "Moon",		  "Mon", "☽" };
Virtue north_n = { NORTH_N, "North Node", "Nor", "☊" };
Virtue south_n = { SOUTH_N, "South Node", "Sou", "☋" };

Virtue aries	   = { ARIES,		"Aries",		"Ari", "♈" };
Virtue taurus	   = { TAURUS,		"Taurus",		"Tau", "♉" };
Virtue gemini	   = { GEMINI,		"Gemini",		"Gem", "♊" };
Virtue cancer	   = { CANCER,		"Cancer",		"Can", "♋" };
Virtue leo		   = { LEO,			"Leo",			"Leo", "♌" };
Virtue virgo	   = { VIRGO,		"Virgo",		"Vir", "♍" };
Virtue libra	   = { LIBRA,		"Libra",		"Lib", "♎" };
Virtue scorpio	   = { SCORPIO,		"Scorpio",		"Sco", "♏" };
Virtue sagittarius = { SAGITTARIUS, "Sagittarius",  "Sag", "♐" };
Virtue capricorn   = { CAPRICORN,	"Capricorn",	"Cap", "♑" };
Virtue aquarius    = { AQUARIUS,	"Aquarius",		"Aqu", "♒" };
Virtue pisces	   = { PISCES,		"Pisces",		"Pis", "♓" };

Virtue *ptr_virtues[25] =
{
	&fire, &air, &water, &earth,
	
	&saturn, &jupiter, &mars, &sun, &venus,
	&mercury, &moon, &north_n, &south_n,
	
	&aries, &taurus, &gemini, &cancer,
	&leo, &virgo, &libra, &scorpio,
	&sagittarius, &capricorn, &aquarius, &pisces
};
