#include "virtues.h"
#include <string.h>

static Virtue fire;
static Virtue air;
static Virtue water;
static Virtue earth;

static Virtue saturn;
static Virtue jupiter;
static Virtue mars;
static Virtue sun;
static Virtue venus;
static Virtue mercury;
static Virtue moon;
static Virtue north_n;
static Virtue south_n;

static Virtue aries;
static Virtue taurus;
static Virtue gemini;
static Virtue cancer;
static Virtue leo;
static Virtue virgo;
static Virtue libra;
static Virtue scorpio;
static Virtue sagittarius;
static Virtue capricorn;
static Virtue aquarius;
static Virtue pisces;

Virtue *ptr_virtues[25];

static void init_elements(void)
{
	strcpy(fire.name, "Fire");
	strcpy(fire.abbr, "Fire");
	strcpy(fire.symbol, "♣");
	fire.id = FIRE;
	ptr_virtues[FIRE] = &fire;
	
	strcpy(air.name, "Air");
	strcpy(air.abbr, "Air");
	strcpy(air.symbol, "♠");
	air.id = AIR;
	ptr_virtues[AIR] = &air;
	
	strcpy(water.name, "Water");
	strcpy(water.abbr, "Water");
	strcpy(water.symbol, "♥");
	water.id = WATER;
	ptr_virtues[WATER] = &water;
	
	strcpy(earth.name, "Water");
	strcpy(earth.abbr, "Water");
	strcpy(earth.symbol, "♦");
	earth.id  = EARTH;
	ptr_virtues[EARTH] = &earth;
}

void init_virtues(void)
{
	init_elements();
}
