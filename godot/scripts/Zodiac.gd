extends Node

const Power    = preload("res://scripts/Power.gd")
const Elements = preload("res://scripts/Elements.gd")

class Base extends Power:
	var element

class Aries extends Base:
	func _init():
		name_string = "Aries"
		symbol      = "A"
		element     = Elements.Fire.new()
		color       = element.color

class Leo extends Base:
	func _init():
		name_string = "Leo"
		symbol      = "L"
		element     = Elements.Fire.new()
		color       = element.color

class Sagittarius extends Base:
	func _init():
		name_string = "Sagittarius"
		symbol      = "S"
		element     = Elements.Fire.new()
		color       = element.color

class Capricorn extends Base:
	func _init():
		name_string = "Capricorn"
		symbol      = "C"
		element     = Elements.Earth.new()
		color       = element.color

class Taurus extends Base:
	func _init():
		name_string = "Taurus"
		symbol      = "T"
		element     = Elements.Earth.new()
		color       = element.color

class Virgo extends Base:
	func _init():
		name_string = "Virgo"
		symbol      = "V"
		element     = Elements.Earth.new()
		color       = element.color

class Libra extends Base:
	func _init():
		name_string = "Libra"
		symbol      = "L"
		element     = Elements.Air.new()
		color       = element.color

class Aquarius extends Base:
	func _init():
		name_string = "Aquarius"
		symbol      = "A"
		element     = Elements.Air.new()
		color       = element.color

class Gemini extends Base:
	func _init():
		name_string = "Gemini"
		symbol      = "G"
		element     = Elements.Air.new()
		color       = element.color

class Cancer extends Base:
	func _init():
		name_string = "Cancer"
		symbol      = "C"
		element     = Elements.Water.new()
		color       = element.color

class Scorpio extends Base:
	func _init():
		name_string = "Scorpio"
		symbol      = "S"
		element     = Elements.Water.new()
		color       = element.color

class Pisces extends Base:
	func _init():
		name_string = "Pisces"
		symbol      = "P"
		element     = Elements.Water.new()
		color       = element.color
