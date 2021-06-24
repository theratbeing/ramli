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
	
	$Selected/Clear.connect("pressed", self, "on_figure_clear")
	$Selected/Remove.connect("pressed", self, "on_figure_removed")
	$Selected/OK.connect("pressed", self, "on_figure_ok")

func set_selection(array):
	selection = array

func on_figure_selected(figure):
	selection.append(figure)
	var selected = Clickable.instance()
	selected.set_figure(figure)
	$Selected/Figures.add_child(selected)
	
	_reenable_buttons()

func on_figure_removed():
	var figures = $Selected/Figures
	if (figures.get_child_count() > 0):
		var node = figures.get_child(figures.get_child_count() - 1)
		node.queue_free()
		selection.pop_back()
	
	_reenable_buttons()

func on_figure_clear():
	selection.clear()
	var figures = $Selected/Figures
	if (figures.get_child_count() > 0):
		for child in figures.get_children():
			figures.remove_child(child)
			child.queue_free()
	
	_reenable_buttons()

func _reenable_buttons():
	if (selection.size() == 4):
		$Selected/OK.disabled = false
		for child in $Selection.get_children():
			child.disabled = true
	else:
		$Selected/OK.disabled = true
		
		if (selection.size() > 0):
			$Selected/Clear.disabled  = false
			$Selected/Remove.disabled = false
		
		if ($Selection.get_child(0).disabled):
			for child in $Selection.get_children():
				child.disabled = false

func on_figure_ok():
	if (selection.size() == 4):
		emit_signal("done_selecting")
