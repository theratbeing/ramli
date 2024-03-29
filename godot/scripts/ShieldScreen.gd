extends Control

func _ready():
	$Chart.connect("screen_highlight_figure", self, "on_highlight")
	$Chart.connect("screen_lowlight_figure", self, "on_lowlight")
	
	$Figures.connect("screen_highlight_figure", self, "on_highlight")
	$Figures.connect("screen_lowlight_figure", self, "on_lowlight")

func setup_chart(chart_data):
	$Chart.set_chart(chart_data.figure_array)
	$Figures.set_chart(chart_data.figure_array)
	$InfoPanel.set_querent(chart_data.querent_name)
	$InfoPanel.set_question(chart_data.question_text)
	
	var time        = chart_data.date_time
	var time_format = "%d/%d/%d %d:%d"
	var time_stamp  = time_format % \
	[time["year"], time["month"], time["day"],\
	time["hour"], time["minute"]]
	
	$InfoPanel.set_date(time_stamp)

func on_highlight(house):
	$Chart.set_highlight(house)
	$Figures.set_highlight(house)

func on_lowlight(house):
	$Chart.set_lowlight(house)
	$Figures.set_lowlight(house)
