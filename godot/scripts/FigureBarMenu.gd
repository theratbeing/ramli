extends VBoxContainer

var show_similar = false

func _init():
	var Bar = load("res://scenes/FigureBar.tscn")
	for _i in range(15):
		var new_bar = Bar.instance()
		add_child(new_bar)

func _ready():
	for child in get_children():
		child.connect("highlight_figure", self, "on_highlight")
		child.connect("lowlight_figure", self, "on_lowlight")

func set_chart(chart):
	var i = 0
	for child in get_children():
		child.set_figure(chart[i])
		i += 1

func show_house(house):
	var children = get_children()
	children[house - 1].highlight_house(house)

func on_highlight(house):
	pass

func on_lowlight(house):
	pass
