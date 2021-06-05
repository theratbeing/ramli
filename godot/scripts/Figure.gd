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

func from_enum(number):
	pass

func from_array(array):
	pass
