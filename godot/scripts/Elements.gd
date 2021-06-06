extends Node

const Power = preload("res://scripts/Power.gd")

# Definition
class Fire extends Power:
	func _init():
		name_string = "Fire"
		color  = Color.red
		symbol = load("res://sprites/element/fire.png")

class Air extends Power:
	func _init():
		name_string = "Air"
		color = Color.yellow
		symbol = load("res://sprites/element/air.png")

class Water extends Power:
	func _init():
		name_string = "Water"
		color = Color.blue
		symbol = load("res://sprites/element/water.png")

class Earth extends Power:
	func _init():
		name_string = "Earth"
		color = Color.green
		symbol = load("res://sprites/element/earth.png")
