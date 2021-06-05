extends Node

const Power    = preload("res://scripts/Power.gd")
const Elements = preload("res://scripts/Elements.gd")

class Base extends Power:
	var element

class Aries extends Base:
	func _init():
		name_string = "Aries"
		symbol      = load("res://sprites/zodiac/aries.png")
		element     = Elements.Fire.new()
		color       = element.color

class Leo extends Base:
	func _init():
		name_string = "Leo"
		symbol      = load("res://sprites/zodiac/leo.png")
		element     = Elements.Fire.new()
		color       = element.color

class Sagittarius extends Base:
	func _init():
		name_string = "Sagittarius"
		symbol      = load("res://sprites/zodiac/sagittarius.png")
		element     = Elements.Fire.new()
		color       = element.color

class Capricorn extends Base:
	func _init():
		name_string = "Capricorn"
		symbol      = load("res://sprites/zodiac/capricorn.png")
		element     = Elements.Earth.new()
		color       = element.color

class Taurus extends Base:
	func _init():
		name_string = "Taurus"
		symbol      = load("res://sprites/zodiac/taurus.png")
		element     = Elements.Earth.new()
		color       = element.color

class Virgo extends Base:
	func _init():
		name_string = "Virgo"
		symbol      = load("res://sprites/zodiac/virgo.png")
		element     = Elements.Earth.new()
		color       = element.color

class Libra extends Base:
	func _init():
		name_string = "Libra"
		symbol      = load("res://sprites/zodiac/libra.png")
		element     = Elements.Air.new()
		color       = element.color

class Aquarius extends Base:
	func _init():
		name_string = "Aquarius"
		symbol      = load("res://sprites/zodiac/aquarius.png")
		element     = Elements.Air.new()
		color       = element.color

class Gemini extends Base:
	func _init():
		name_string = "Gemini"
		symbol      = load("res://sprites/zodiac/gemini.png")
		element     = Elements.Air.new()
		color       = element.color

class Cancer extends Base:
	func _init():
		name_string = "Cancer"
		symbol      = load("res://sprites/zodiac/cancer.png")
		element     = Elements.Water.new()
		color       = element.color

class Scorpio extends Base:
	func _init():
		name_string = "Scorpio"
		symbol      = load("res://sprites/zodiac/scorpio.png")
		element     = Elements.Water.new()
		color       = element.color

class Pisces extends Base:
	func _init():
		name_string = "Pisces"
		symbol      = load("res://sprites/zodiac/pisces.png")
		element     = Elements.Water.new()
		color       = element.color
