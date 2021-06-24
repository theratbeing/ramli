extends Node

var Figures = preload("res://scripts/Figure.gd").new()

func _init():
	randomize()

func generate_mothers():
	var output = []
	for _i in range(4):
		var points = []
		for _j in range(4):
			points.append(randi() % 2)
		output.append(points)
	return output

func combine_points(pa, pb):
	assert(pa.size() == 4 and pb.size() == 4)
	var output = []
	for i in range(4):
		output.append((pa[i] + pb[i]) % 2)
	return output

func random_mothers():
	var output = []
	for _i in range(4):
		var figure = Figures.from_enum(randi() % 16)
		output.append(figure)
	
	return output

func make_chart_from_figures(figs):
	assert(figs.size() == 4)
	var mothers = []
	for fig in figs:
		mothers.append(fig.point_array)
	
	var chart = calculate_chart(mothers)
	return convert_to_figures(chart)

func calculate_chart(mothers):
	# Expects 4x4 array of int
	assert(mothers.size() == 4)
	var daughters = []
	for _i in range(4):
		daughters.append([0, 0, 0, 0])
	
	for i in range(4):
		for j in range(4):
			daughters[i][j] = mothers[j][i]
	
	var chart  = mothers + daughters
	var nieces = []
	for i in range(0, 8, 2):
		nieces.append(combine_points(chart[i], chart[i+1]))
	
	chart += nieces
	var witnesses = []
	for i in range(0, 4, 2):
		witnesses.append(combine_points(nieces[i], nieces[i+1]))
	
	chart += witnesses
	chart.append(combine_points(witnesses[0], witnesses[1]))
	assert(chart.size() == 15)
	return chart

func convert_to_figures(chart):
	assert(chart.size() == 15)
	var output = []
	for array in chart:
		output.append(Figures.from_array(array))
	return output
