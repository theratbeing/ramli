extends Node

const Constants = preload("res://scripts/Constants.gd")
const Elements  = preload("res://scripts/Elements.gd")
const Planets   = preload("res://scripts/Planets.gd")
const Zodiac    = preload("res://scripts/Zodiac.gd")

class Base extends Node:
	var number
	var name_string
	var point_array
	
	var element
	var planet
	var zodiac

class Via extends Base:
	func _init():
		number		= Constants.Figure.VIA
		name_string = "Via"
		point_array = [1, 1, 1, 1]
		element		= Elements.Water.new()
		planet		= Planets.Moon.new()
		zodiac		= {
			Constants.System.AGRIPPA : Zodiac.Cancer.new(),
			Constants.System.GERARDO : Zodiac.Leo.new()
		}

class Populus extends Base:
	func _init():
		number		= Constants.Figure.POPULUS
		name_string = "Populus"
		point_array = [0, 0, 0, 0]
		element		= Elements.Water.new()
		planet		= Planets.Moon.new()
		zodiac		= {
			Constants.System.AGRIPPA : Zodiac.Cancer.new(),
			Constants.System.GERARDO : Zodiac.Capricorn.new()
		}

class Tristitia extends Base:
	func _init():
		number		= Constants.Figure.TRISTITIA
		name_string = "Tristitia"
		point_array = [0, 0, 0, 1]
		element		= Elements.Earth.new()
		planet		= Planets.Saturn.new()
		zodiac		= {
			Constants.System.AGRIPPA : Zodiac.Aquarius.new(),
			Constants.System.GERARDO : Zodiac.Scorpio.new()
		}

class Laetitia extends Base:
	func _init():
		number		= Constants.Figure.LAETITIA
		name_string = "Laetitia"
		point_array = [1, 0, 0, 0]
		element		= Elements.Air.new()
		planet		= Planets.Jupiter.new()
		zodiac		= {
			Constants.System.AGRIPPA : Zodiac.Pisces.new(),
			Constants.System.GERARDO : Zodiac.Taurus.new()
		}

class Rubeus extends Base:
	func _init():
		number		= Constants.Figure.RUBEUS
		name_string = "Rubeus"
		point_array = [0, 1, 0, 0]
		element		= Elements.Air.new()
		planet		= Planets.Mars.new()
		zodiac		= {
			Constants.System.AGRIPPA : Zodiac.Scorpio.new(),
			Constants.System.GERARDO : Zodiac.Gemini.new()
		}

class Albus extends Base:
	func _init():
		number		= Constants.Figure.ALBUS
		name_string = "Albus"
		point_array = [0, 0, 1, 0]
		element		= Elements.Water.new()
		planet		= Planets.Mercury.new()
		zodiac		= {
			Constants.System.AGRIPPA : Zodiac.Gemini.new(),
			Constants.System.GERARDO : Zodiac.Cancer.new()
		}

class FortunaMajor extends Base:
	func _init():
		number		= Constants.Figure.FORTUNA_MAJOR
		name_string = "Fortuna Major"
		point_array = [0, 0, 1, 1]
		element		= Elements.Earth.new()
		planet		= Planets.Sun.new()
		zodiac		= {
			Constants.System.AGRIPPA : Zodiac.Leo.new(),
			Constants.System.GERARDO : Zodiac.Aquarius.new()
		}

class FortunaMinor extends Base:
	func _init():
		number		= Constants.Figure.FORTUNA_MINOR
		name_string = "Fortuna Minor"
		point_array = [1, 1, 0, 0]
		element		= Elements.Fire.new()
		planet		= Planets.Sun.new()
		zodiac		= {
			Constants.System.AGRIPPA : Zodiac.Leo.new(),
			Constants.System.GERARDO : Zodiac.Taurus.new()
		}

class Acquisitio extends Base:
	func _init():
		number		= Constants.Figure.ACQUISITIO
		name_string = "Acquisitio"
		point_array = [0, 1, 0, 1]
		element		= Elements.Air.new()
		planet		= Planets.Jupiter.new()
		zodiac		= {
			Constants.System.AGRIPPA : Zodiac.Sagittarius.new(),
			Constants.System.GERARDO : Zodiac.Aries.new()
		}

class Amissio extends Base:
	func _init():
		number		= Constants.Figure.AMISSIO
		name_string = "Amissio"
		point_array = [1, 0, 1, 0]
		element		= Elements.Fire.new()
		planet		= Planets.Venus.new()
		zodiac		= {
			Constants.System.AGRIPPA : Zodiac.Taurus.new(),
			Constants.System.GERARDO : Zodiac.Scorpio.new()
		}

class Conjunctio extends Base:
	func _init():
		number		= Constants.Figure.CONJUNCTIO
		name_string = "Conjunctio"
		point_array = [0, 1, 1, 0]
		element		= Elements.Air.new()
		planet		= Planets.Mercury.new()
		zodiac		= {
			Constants.System.AGRIPPA : Zodiac.Virgo.new(),
			Constants.System.GERARDO : Zodiac.Virgo.new()
		}

class Carcer extends Base:
	func _init():
		number		= Constants.Figure.CARCER
		name_string = "Carcer"
		point_array = [1, 0, 0, 1]
		element		= Elements.Earth.new()
		planet		= Planets.Saturn.new()
		zodiac		= {
			Constants.System.AGRIPPA : Zodiac.Capricorn.new(),
			Constants.System.GERARDO : Zodiac.Pisces.new()
		}

class Puer extends Base:
	func _init():
		number		= Constants.Figure.PUER
		name_string = "Puer"
		point_array = [1, 1, 0, 1]
		element		= Elements.Air.new()
		planet		= Planets.Mars.new()
		zodiac		= {
			Constants.System.AGRIPPA : Zodiac.Aries.new(),
			Constants.System.GERARDO : Zodiac.Gemini.new()
		}

class Puella extends Base:
	func _init():
		number		= Constants.Figure.PUELLA
		name_string = "Puella"
		point_array = [1, 0, 1, 1]
		element		= Elements.Water.new()
		planet		= Planets.Venus.new()
		zodiac		= {
			Constants.System.AGRIPPA : Zodiac.Libra.new(),
			Constants.System.GERARDO : Zodiac.Libra.new()
		}

class CaputDraconis extends Base:
	func _init():
		number		= Constants.Figure.CAPUT_DRACO
		name_string = "Caput Draconis"
		point_array = [0, 1, 1, 1]
		element		= Elements.Earth.new()
		planet		= Planets.NorthNode.new()
		zodiac		= {
			Constants.System.AGRIPPA : Zodiac.Virgo.new(),
			Constants.System.GERARDO : Zodiac.Virgo.new()
		}

class CaudaDraconis extends Base:
	func _init():
		number		= Constants.Figure.CAUDA_DRACO
		name_string = "Cauda Draconis"
		point_array = [1, 1, 1, 0]
		element		= Elements.Fire.new()
		planet		= Planets.SouthNode.new()
		zodiac		= {
			Constants.System.AGRIPPA : Zodiac.Sagittarius.new(),
			Constants.System.GERARDO : Zodiac.Sagittarius.new()
		}

func from_enum(number):
	assert(number >= 0 and number < 16)
	match number:
		Constants.Figure.VIA:
			return Via.new()
		Constants.Figure.POPULUS:
			return Populus.new()
		Constants.Figure.TRISTITIA:
			return Tristitia.new()
		Constants.Figure.LAETITIA:
			return Laetitia.new()
		Constants.Figure.RUBEUS:
			return Rubeus.new()
		Constants.Figure.ALBUS:
			return Albus.new()
		Constants.Figure.FORTUNA_MAJOR:
			return FortunaMajor.new()
		Constants.Figure.FORTUNA_MINOR:
			return FortunaMinor.new()
		Constants.Figure.ACQUISITIO:
			return Acquisitio.new()
		Constants.Figure.AMISSIO:
			return Amissio.new()
		Constants.Figure.CONJUNCTIO:
			return Conjunctio.new()
		Constants.Figure.CARCER:
			return Carcer.new()
		Constants.Figure.PUER:
			return Puer.new()
		Constants.Figure.PUELLA:
			return Puella.new()
		Constants.Figure.CAPUT_DRACO:
			return CaputDraconis.new()
		Constants.Figure.CAUDA_DRACO:
			return CaudaDraconis.new()

func from_array(array):
	assert(array.size() == 4)
	var total    = 0
	var multiple = 1
	
	for n in array:
		assert(n == 0 or n == 1)
		total += n * multiple
		multiple *= 2
	
	assert(total >= 0 and total < 16)
	return from_enum(total)
