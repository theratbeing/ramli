extends Node

const Figures = preload("res://scripts/Figure.gd")

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
		output.append(pa[i] + pb[i] % 2)
	return output

func calculate_chart(mothers):
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
