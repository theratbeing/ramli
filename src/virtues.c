#include "virtues.h"
#include <string.h>

Virtue fire, air, water, earth;

Virtue saturn, jupiter, mars, sun, venus;
Virtue mercury, moon, north_n, south_n;

Virtue aries, taurus, gemini, cancer;
Virtue leo, virgo, libra, scorpio;
Virtue sagittarius, capricorn, aquarius, pisces;

Virtue *ptr_virtues[25] =
{
	&fire, &air, &water, &earth,
	
	&saturn, &jupiter, &mars, &sun, &venus,
	&mercury, &moon, &north_n, &south_n,
	
	&aries, &taurus, &gemini, &cancer,
	&leo, &virgo, &libra, &scorpio,
	&sagittarius, &capricorn, &aquarius, &pisces
};

static void init_elements(void)
{
	fire.id = FIRE;
	strcpy(fire.name, "Fire");
	strcpy(fire.abbr, "Fir");
	strcpy(fire.symbol, "♣");
	
	air.id = AIR;
	strcpy(air.name, "Air");
	strcpy(air.abbr, "Air");
	strcpy(air.symbol, "♠");
	
	water.id = WATER;
	strcpy(water.name, "Water");
	strcpy(water.abbr, "Wat");
	strcpy(water.symbol, "♥");
	
	earth.id  = EARTH;
	strcpy(earth.name, "Earth");
	strcpy(earth.abbr, "Ear");
	strcpy(earth.symbol, "♦");
}

static void init_planets(void)
{
	saturn.id = SATURN;
	strcpy(saturn.name, "Saturn");
	strcpy(saturn.abbr, "Sat");
	strcpy(saturn.symbol, "♄");
	
	jupiter.id = JUPITER;
	strcpy(jupiter.name, "Jupiter");
	strcpy(jupiter.abbr, "Jup");
	strcpy(jupiter.symbol, "♃");
	
	mars.id = MARS;
	strcpy(mars.name, "Mars");
	strcpy(mars.abbr, "Mar");
	strcpy(mars.symbol, "♂");
	
	sun.id = SUN;
	strcpy(sun.name, "Sun");
	strcpy(sun.abbr, "Sun");
	strcpy(sun.symbol, "☉");
	
	venus.id = VENUS;
	strcpy(venus.name, "Venus");
	strcpy(venus.abbr, "Ven");
	strcpy(venus.symbol, "♀");
	
	mercury.id = MERCURY;
	strcpy(mercury.name, "Mercury");
	strcpy(mercury.abbr, "Mer");
	strcpy(mercury.symbol, "☿");
	
	moon.id = MOON;
	strcpy(moon.name, "Moon");
	strcpy(moon.abbr, "Mon");
	strcpy(moon.symbol, "☽");
	
	north_n.id = NORTH_N;
	strcpy(north_n.name, "North Node");
	strcpy(north_n.abbr, "Nor");
	strcpy(north_n.symbol, "☊");
	
	south_n.id = SOUTH_N;
	strcpy(south_n.name, "South Node");
	strcpy(south_n.abbr, "Sou");
	strcpy(south_n.symbol, "☋");
}

static void init_zodiac(void)
{
	aries.id = ARIES;
	strcpy(aries.name, "Aries");
	strcpy(aries.abbr, "Ari");
	strcpy(aries.symbol, "♈");
	
	taurus.id = TAURUS;
	strcpy(taurus.name, "Taurus");
	strcpy(taurus.abbr, "Tau");
	strcpy(taurus.symbol, "♉");
	
	gemini.id = GEMINI;
	strcpy(gemini.name, "Gemini");
	strcpy(gemini.abbr, "Gem");
	strcpy(gemini.symbol, "♊");
	
	cancer.id = CANCER;
	strcpy(cancer.name, "Cancer");
	strcpy(cancer.abbr, "Can");
	strcpy(cancer.symbol, "♋");
	
	leo.id = LEO;
	strcpy(leo.name, "Leo");
	strcpy(leo.abbr, "Leo");
	strcpy(leo.symbol, "♌");
	
	virgo.id = VIRGO;
	strcpy(virgo.name, "Virgo");
	strcpy(virgo.abbr, "Vir");
	strcpy(virgo.symbol, "♍");
	
	libra.id = LIBRA;
	strcpy(libra.name, "Libra");
	strcpy(libra.abbr, "Lib");
	strcpy(libra.symbol, "♎");
	
	scorpio.id = SCORPIO;
	strcpy(scorpio.name, "Scorpio");
	strcpy(scorpio.abbr, "Sco");
	strcpy(scorpio.symbol, "♏");
	
	sagittarius.id = SAGITTARIUS;
	strcpy(sagittarius.name, "Sagittarius");
	strcpy(sagittarius.abbr, "Sag");
	strcpy(sagittarius.symbol, "♐");
	
	capricorn.id = CAPRICORN;
	strcpy(capricorn.name, "Capricorn");
	strcpy(capricorn.abbr, "Cap");
	strcpy(capricorn.symbol, "♑");
	
	aquarius.id = AQUARIUS;
	strcpy(aquarius.name, "Aquarius");
	strcpy(aquarius.abbr, "Aqu");
	strcpy(aquarius.symbol, "♒");
	
	pisces.id = PISCES;
	strcpy(pisces.name, "Pisces");
	strcpy(pisces.abbr, "Pis");
	strcpy(pisces.symbol, "♓");
}

void init_virtues(void)
{
	init_elements();
	init_planets();
	init_zodiac();
}
