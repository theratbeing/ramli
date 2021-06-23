extends Node

const ReadingForm     = preload("res://scenes/ReadingForm.tscn")
const CardSelection   = preload("res://scenes/CardSelection.tscn")
const FigureSelection = preload("res://scenes/FigureSelection.tscn")
const ShieldScreen    = preload("res://scenes/ShieldScreen.tscn")
const HouseScreen     = preload("res://scenes/HouseScreen.tscn")

const Generator = preload("res://scripts/Generator.gd")
const ChartData = preload("res://scripts/ChartData.gd")

var generator
var chart_data
var current_scene
var figure_selection

func _ready():
	generator        = Generator.new()
	chart_data       = ChartData.new()
	figure_selection = []
	current_scene  = ReadingForm.instance()
	add_child(current_scene)
	current_scene.set_data(chart_data)
	current_scene.connect("input_ok", self, "on_Form_ok")
	current_scene.connect("input_cancel", self, "on_Form_cancel")

func on_Form_ok():
	current_scene.queue_free()
	
	match chart_data.generation_method:
		chart_data.Method.AUTOMATIC:
			start_figure_automatic()
		chart_data.Method.SELECTION:
			start_figure_selection()
		chart_data.Method.MANUAL:
			start_figure_manual()

func on_Form_cancel():
	pass


# Figure selection screens
func start_figure_automatic():
	figure_selection = generator.random_mothers()
	on_done_selecting()

func start_figure_selection():
	current_scene = CardSelection.instance()
	add_child(current_scene)
	current_scene.set_selection(figure_selection)
	current_scene.connect("done_selecting", self, "on_done_selecting")

func start_figure_manual():
	current_scene = FigureSelection.instance()
	add_child(current_scene)
	current_scene.set_selection(figure_selection)
	current_scene.connect("done_selecting", self, "on_done_selecting")

func on_done_selecting():
	if (chart_data.generation_method != chart_data.Method.AUTOMATIC):
		current_scene.queue_free()
	
	chart_data.date_time    = OS.get_datetime()
	chart_data.figure_array = generator.make_chart_from_figures(figure_selection)
	
	if (chart_data.is_shield_chart()):
		start_chart_shield()
	else:
		start_chart_house()


# Chart drawing screens
func start_chart_shield():
	current_scene = ShieldScreen.instance()
	add_child(current_scene)
	current_scene.setup_chart(chart_data)

func start_chart_house():
	current_scene = HouseScreen.instance()
	add_child(current_scene)
	current_scene.setup_chart(chart_data)
