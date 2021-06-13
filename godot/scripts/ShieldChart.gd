extends TextureRect

var children = []

func _init():
	children = get_children()

func set_chart(chart):
	var i = 0
	for child in children:
		child.set_figure(chart[i])
		i += 1

func lowlight_all():
	for child in children:
		child.lowlight()

func set_highlight(house):
	children[house].highlight()

func set_lowlight(house):
	children[house].lowlight()
