extends Control

var CardButton = preload("res://scenes/Card.tscn")
var figures    = []
var selection  = []

var debug_string = "selected figure: %d"

func _init():
	randomize()
	for i in range(16):
		for _j in range(4):
			figures.append(i)

func _ready():
	figures.shuffle()
	
	for f in figures:
		var card = CardButton.instance()
		card.figure = f
		card.connect("selected_figure", self, "on_card_select")
		$Selection.add_child(card)

func on_card_select(figure):
	selection.append(figure)
	var message = debug_string % figure
	print_debug(message)
	if selection.size() == 4:
		for node in $Selection.get_children():
			node.disabled = true
		print_debug("done selecting")
