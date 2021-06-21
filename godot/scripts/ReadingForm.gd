extends Control

const ChartData = preload("res://scripts/ChartData.gd")

signal input_ok
signal input_cancel

var data

func _ready():
	data = ChartData.new()
	
	for i in range(1, 13):
		$Panel/House/Number.add_item(str(i))
	
	$Panel/Chart/House.connect("toggled", self, "on_house_toggled")
	$Panel/Continue.connect("pressed", self, "on_continue_pressed")
	$Panel/Cancel.connect("pressed", self, "on_cancel_pressed")

func on_house_toggled(is_on):
	if (is_on):
		$Panel/House/Number.disabled = false
	else:
		$Panel/House/Number.disabled = true

func on_continue_pressed():
	data.querent_name  = $Panel/Querent/Line.text
	data.question_text = $Panel/Question/Line.text
	data.house_number  = $Panel/House/Number.selected + 1
	
	if ($Panel/Chart/Shield.pressed):
		data.set_shield_chart()
	else:
		data.set_house_chart()
	
	if ($Panel/Generator/Automatic.pressed):
		data.set_automatic()
	elif ($Panel/Generator/Selection.pressed):
		data.set_selection()
	else:
		data.set_manual()
	
	emit_signal("input_ok")

func on_cancel_pressed():
	emit_signal("input_cancel")
