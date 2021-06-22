extends Control

const Figure = preload("res://scripts/Figure.gd")

var CardButton = preload("res://scenes/Card.tscn")
var figures    = []
var selection

var debug_string = "selected figure: %s"

signal done_selecting

func _init():
	randomize()
	var generator = Figure.new()
	for i in range(16):
		for _j in range(4):
			figures.append(generator.from_enum(i))

func _ready():
	figures.shuffle()
	
	for f in figures:
		var card = CardButton.instance()
		card.figure = f
		card.connect("selected", self, "on_card_select")
		$Selection.add_child(card)

func set_selection(array):
	selection = array

func on_card_select(figure):
	selection.append(figure)
	var message = debug_string % figure.name_string
	print_debug(message)
	if selection.size() == 4:
		print_debug("done selecting")
		emit_signal("done_selecting")
		
		for node in $Selection.get_children():
			node.disabled = true
