extends TextureButton

var figure

signal selected(figure)

func _ready():
	connect("pressed", self, "on_pressed")

func on_pressed():
	emit_signal("selected", figure)
	disabled = true
