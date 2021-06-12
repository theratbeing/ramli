extends VBoxContainer

var textures = []

func _init():
	textures.resize(2)
	textures[0] = load("res://sprites/point_2.png")
	textures[1] = load("res://sprites/point_1.png")
	
func set_figure(figure):
	var i = 0	
	for child in get_children():
		child.texture = textures[figure.point_array[i]]
		i += 1
