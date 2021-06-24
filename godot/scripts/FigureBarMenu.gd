extends Panel

var show_similar = false
var children = []

signal screen_highlight_figure(index)
signal screen_lowlight_figure(index)

func _ready():
	var Bar = load("res://scenes/FigureBar.tscn")
	for _i in range(15):
		var new_bar = Bar.instance()
		$Container.add_child(new_bar)
	
	children = $Container.get_children()
	
	var house = 1
	for child in children:
		child.set_house(house)
		child.connect("highlight_figure", self, "on_highlight")
		child.connect("lowlight_figure", self, "on_lowlight")
		house += 1

func get_items():
	return $Container.get_children()

func highlight_similar(boolean):
	show_similar = boolean

func set_chart(chart):
	var i = 0
	for child in children:
		child.set_figure(chart[i])
		i += 1

func show_house(house):
	children[house - 1].highlight_house()

func lowlight_all():
	for child in children:
		child.lowlight()

func on_highlight(house):
	emit_signal("screen_highlight_figure", house)
	set_highlight(house)

func set_highlight(house):
	if (show_similar):
		var number = children[house].figure.number
		for child in children:
			if (child.figure.number == number):
				child.highlight()
	else:
		children[house].highlight()

func on_lowlight(house):
	emit_signal("screen_lowlight_figure", house)
	set_lowlight(house)

func set_lowlight(house):
	if (show_similar):
		for child in children:
			child.lowlight()
	else:
		children[house].lowlight()
