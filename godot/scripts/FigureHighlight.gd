extends TextureRect

const Figure = preload("res://scripts/Figure.gd")

var texture_normal
var texture_hover
var figure

signal highlight_figure(index)
signal lowlight_figure(index)

func _init():
	texture_normal = load("res://sprites/border_normal.png")
	texture_hover  = load("res://sprites/border_hover.png")

func _ready():
	connect("mouse_entered", self, "on_mouse_entered")
	connect("mouse_exited", self, "on_mouse_exited")

func set_figure(fig):
	$FigureTextures.set_figure(fig)
	figure = fig

func lowlight():
	texture = texture_normal

func highlight():
	texture = texture_hover

func on_mouse_entered():
	texture = texture_hover
	emit_signal("highlight_figure", get_index())

func on_mouse_exited():
	texture = texture_normal
	emit_signal("lowlight_figure", get_index())
