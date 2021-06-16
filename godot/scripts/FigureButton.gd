extends TextureButton

var figure

signal selected(figure)

func set_figure(fig):
	figure = fig
	$FigureTextures.set_figure(fig)

func _ready():
	connect("pressed", self, "on_button_pressed")

func on_button_pressed():
	emit_signal("selected", figure)
