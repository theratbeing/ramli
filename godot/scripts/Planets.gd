extends Node

const Power = preload("res://scripts/Power.gd")

class Saturn extends Power:
	func _init():
		name_string = "Saturn"
		color  = Color.black
		symbol = "S"

class Jupiter extends Power:
	func _init():
		name_string = "Jupiter"
		color  = Color.blue
		symbol = "J"

class Mars extends Power:
	func _init():
		name_string = "Mars"
		color  = Color.red
		symbol = "M"

class Sun extends Power:
	func _init():
		name_string = "Sun"
		color  = Color.yellow
		symbol = "S"

class Venus extends Power:
	func _init():
		name_string = "Venus"
		color  = Color.green
		symbol = "V"

class Mercury extends Power:
	func _init():
		name_string = "Mercury"
		color  = Color.orange
		symbol = "M"

class Moon extends Power:
	func _init():
		name_string = "Moon"
		color  = Color.purple
		symbol = "M"

class NorthNode extends Power:
	func _init():
		name_string = "North Node"
		color  = Color.gray
		symbol = "N"

class SouthNode extends Power:
	func _init():
		name_string = "South Node"
		color  = Color.gray
		symbol = "S"
