extends "res://scripts/FigureHighlight.gd"

func _init():
	texture_normal = load("res://sprites/borderless_normal.png")
	texture_hover  = load("res://sprites/borderless_hover.png")

func _ready():
	connect("mouse_entered", self, "on_mouse_entered")
	connect("mouse_exited", self, "on_mouse_exited")
