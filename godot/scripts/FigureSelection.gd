extends Control

const Figure    = preload("res://scripts/Figure.gd")
const Clickable = preload("res://scenes/FigureButton.tscn")

var selection

signal done_selecting

func _ready():
	var generator = Figure.new()
	for i in range(16):
		var figure = generator.from_enum(i)
		var button = Clickable.instance()
		button.set_figure(figure)
		button.connect("selected", self, "on_figure_selected")
		$Selection.add_child(button)

func set_selection(array):
	selection = array

func on_figure_selected(figure):
	selection.append(figure)
	var selected = Clickable.instance()
	selected.set_figure(figure)
	$Selected.add_child(selected)
	
	if (selection.size() == 4):
		for child in $Selection.get_children():
			child.disabled = true
		
		emit_signal("done_selecting")

