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
	var cards = []
	
	for f in figures:
		var card = CardButton.instance()
		card.figure = f
		card.connect("selected_figure", self, "on_card_select")
		cards.append(card)
	
	for i in range(0, 16):
		$Selection/Row1.add_child(cards[i])
	
	for i in range(16, 32):
		$Selection/Row2.add_child(cards[i])
	
	for i in range(32, 48):
		$Selection/Row3.add_child(cards[i])
	
	for i in range(48, 64):
		$Selection/Row4.add_child(cards[i])

func on_card_select(figure):
	selection.append(figure)
	var message = debug_string % figure
	print_debug(message)
	if selection.size() == 4:
		print_debug("done selecting")
