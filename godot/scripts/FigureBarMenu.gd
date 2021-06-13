extends VBoxContainer

var show_similar = false
var children = []

signal highlight_figure(index)
signal lowlight_figure(index)

func _init():
	var Bar = load("res://scenes/FigureBar.tscn")
	for _i in range(15):
		var new_bar = Bar.instance()
		add_child(new_bar)

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

func show_house(house):
	children[house - 1].highlight_house(house)

func lowlight_all():
	for child in children:
		child.lowlight()

func set_highlight(house):
	children[house].highlight()

func set_lowlight(house):
	children[house].lowlight()

func on_highlight(house):
	emit_signal("highlight_figure", house)

func on_lowlight(house):
	emit_signal("lowlight_figure", house)
