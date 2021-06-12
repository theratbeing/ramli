extends TextureRect

var texture_normal
var texture_hover

signal highlight_figure(index)
signal lowlight_figure(index)

func _ready():
	texture_normal = load("res://sprites/border_normal.png")
	texture_hover  = load("res://sprites/border_hover.png")
	
	connect("mouse_entered", self, "on_mouse_entered")
	connect("mouse_exited", self, "on_mouse_exited")

func set_figure(figure):
	$FigureTextures.set_figure(figure)

func on_mouse_entered():
	texture = texture_hover
	emit_signal("highlight_figure", get_index())

func on_mouse_exited():
	texture = texture_normal
	emit_signal("lowlight_figure", get_index())