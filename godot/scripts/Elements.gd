extends Node

const Power = preload("res://scripts/Power.gd")

# Definition
class Fire extends Power:
	func _init():
		name_string = "Fire"
		color  = Color.red
		symbol = "F"

class Air extends Power:
	func _init():
		name_string = "Air"
		color = Color.yellow
		symbol = "A"

class Water extends Power:
	func _init():
		name_string = "Water"
		color = Color.blue
		symbol = "W"

class Earth extends Power:
	func _init():
		name_string = "Earth"
		color = Color.green
		symbol = "E"
