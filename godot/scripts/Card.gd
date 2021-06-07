extends TextureButton

var figure = 0

signal selected_figure

func _ready():
	connect("pressed", self, "on_pressed")

func on_pressed():
	emit_signal("selected_figure", figure)
	disabled = true
