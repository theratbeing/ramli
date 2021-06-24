extends TextureRect

var children = []

signal screen_highlight_figure(index)
signal screen_lowlight_figure(index)

func _ready():
	children = get_children()
	
	for child in children:
		child.connect("highlight_figure", self, "on_highlight")
		child.connect("lowlight_figure", self, "on_lowlight")

func set_chart(chart):
	var i = 0
	for child in children:
		child.set_figure(chart[i])
		i += 1

func on_highlight(house):
	emit_signal("screen_highlight_figure", house)
	set_highlight(house)

func set_highlight(house):
	children[house].highlight()

func on_lowlight(house):
	emit_signal("screen_lowlight_figure", house)
	set_lowlight(house)

func set_lowlight(house):
	children[house].lowlight()
