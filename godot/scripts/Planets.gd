extends Node

const Power = preload("res://scripts/Power.gd")

class Saturn extends Power:
	func _init():
		name_string = "Saturn"
		color  = Color.black
		symbol = load("res://sprites/planet/saturn.png")

class Jupiter extends Power:
	func _init():
		name_string = "Jupiter"
		color  = Color.blue
		symbol = load("res://sprites/planet/jupiter.png")

class Mars extends Power:
	func _init():
		name_string = "Mars"
		color  = Color.red
		symbol = load("res://sprites/planet/mars.png")

class Sun extends Power:
	func _init():
		name_string = "Sun"
		color  = Color.yellow
		symbol = load("res://sprites/planet/sun.png")

class Venus extends Power:
	func _init():
		name_string = "Venus"
		color  = Color.green
		symbol = load("res://sprites/planet/venus.png")

class Mercury extends Power:
	func _init():
		name_string = "Mercury"
		color  = Color.orange
		symbol = load("res://sprites/planet/mercury.png")

class Moon extends Power:
	func _init():
		name_string = "Moon"
		color  = Color.purple
		symbol = load("res://sprites/planet/moon.png")

class NorthNode extends Power:
	func _init():
		name_string = "North Node"
		color  = Color.gray
		symbol = load("res://sprites/planet/north_node.png")

class SouthNode extends Power:
	func _init():
		name_string = "South Node"
		color  = Color.gray
		symbol = load("res://sprites/planet/south_node.png")
