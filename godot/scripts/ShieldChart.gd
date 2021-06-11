extends TextureRect

func set_chart(chart):
	var i = 0
	for child in get_children():
		child.set_figure(chart[i])
		i += 1
