extends Control

signal input_ok
signal input_cancel

func _ready():
	for i in range(1, 13):
		$House/Number.add_item(str(i))
	
	$Chart/House.connect("toggled", self, "on_house_toggled")
	$Continue.connect("pressed", self, "on_continue_pressed")
	$Cancel.connect("pressed", self, "on_cancel_pressed")

func on_house_toggled(is_on):
	if (is_on):
		$House/Number.disabled = false
	else:
		$House/Number.disabled = true

func on_continue_pressed():
	emit_signal("input_ok")

func on_cancel_pressed():
	emit_signal("input_cancel")
