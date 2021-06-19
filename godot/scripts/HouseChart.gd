extends "res://scripts/ShieldChart.gd"

func on_highlight(house):
	var figure = children[house].figure
	for child in children:
		if (child.figure.number == figure.number):
			child.highlight()

func on_lowlight(_house):
	for child in children:
		child.lowlight()
