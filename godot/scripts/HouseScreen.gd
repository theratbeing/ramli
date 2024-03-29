extends Control

func _ready():
	for figure in $Chart.get_children():
		figure.connect("highlight_figure", self, "on_highlight")
		figure.connect("lowlight_figure", self, "on_lowlight")
	
	for figure in $Figures/Container.get_children():
		figure.connect("highlight_figure", self, "on_highlight")
		figure.connect("lowlight_figure", self, "on_lowlight")
	
	$Figures.highlight_similar(true)

func setup_chart(chart_data):
	$Chart.set_chart(chart_data.figure_array)
	$Figures.set_chart(chart_data.figure_array)
	$Figures.show_house(chart_data.house_number)
	$InfoPanel.set_querent(chart_data.querent_name)
	$InfoPanel.set_question(chart_data.question_text)
	
	var time        = chart_data.date_time
	var time_format = "%d/%d/%d %d:%d"
	var time_stamp  = time_format % \
	[time["year"], time["month"], time["day"],\
	time["hour"], time["minute"]]
	
	$InfoPanel.set_date(time_stamp)

func on_highlight(house):
	$Chart.on_highlight(house)
	$Figures.on_highlight(house)

func on_lowlight(house):
	$Chart.on_lowlight(house)
	$Figures.on_lowlight(house)
