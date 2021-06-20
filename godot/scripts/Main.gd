extends Node

const ReadingForm     = preload("res://scenes/ReadingForm.tscn")
const CardSelection   = preload("res://scenes/CardSelection.tscn")
const FigureSelection = preload("res://scenes/FigureSelection.tscn")
const ShieldScreen    = preload("res://scenes/ShieldScreen.tscn")
const HouseScreen     = preload("res://scenes/HouseScreen.tscn")

const Generator = preload("res://scripts/Generator.gd")

# TODO: make a class to contain these data
var generator
var querent_name
var question_text
var date_time
var house_number
var chart_type
var generate_method

func _ready():
	generator = Generator.new()
	var form  = ReadingForm.instance()
	form.name = "Form"
	add_child(form)
	$Form.connect("input_ok", self, "on_Form_ok")
	$Form.connect("input_cancel", self, "on_Form_cancel")

func on_Form_ok():
	# TODO: process this in the form node instead
	querent_name  = $Form/Panel/Querent/Line.text
	question_text = $Form/Panel/Question/Line.text

func on_Form_cancel():
	pass
