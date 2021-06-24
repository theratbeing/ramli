extends TextureRect

const Constants = preload("res://scripts/Constants.gd")

signal highlight_figure(index)
signal lowlight_figure(index)

var figure

func _ready():
	lowlight()
	lowlight_house()
	
	connect("mouse_entered", self, "on_mouse_entered")
	connect("mouse_exited", self, "on_mouse_exited")

func set_figure(figure_):
	figure         = figure_
	$Name.text     = figure.name_string
	$Element.text  = figure.element.symbol
	$Planet.text   = figure.planet.symbol
	$Zodiac1.text  = figure.zodiac[Constants.System.GERARDO].symbol
	$Zodiac2.text  = figure.zodiac[Constants.System.AGRIPPA].symbol

func set_house(num):
	$House.text = str(num)

func highlight_house():
	$HouseHighlight.show()

func lowlight_house():
	$HouseHighlight.hide()

func highlight():
	$Highlight.show()

func lowlight():
	$Highlight.hide()

func on_mouse_entered():
	highlight()
	emit_signal("highlight_figure", get_index())

func on_mouse_exited():
	lowlight()
	emit_signal("lowlight_figure", get_index())
