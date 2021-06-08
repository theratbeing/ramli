extends VBoxContainer

var figure_id
var textures = []
var lines    = []

func _init():
	textures.resize(2)
	textures[0] = load("res://sprites/point_2.png")
	textures[1] = load("res://sprites/point_1.png")
	
	lines.resize(4)
	lines[0] = $Line1
	lines[1] = $Line2
	lines[2] = $Line3
	lines[3] = $Line4

func set_figure(figure):
	figure_id = figure.number
	
	for i in range(4):
		lines[i].texture = textures[figure.point_array[i]]
