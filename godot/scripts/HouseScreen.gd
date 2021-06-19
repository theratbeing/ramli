extends Control

func _ready():
	for figure in $Chart.get_children():
		figure.connect("highlight_figure", self, "on_highlight")
		figure.connect("lowlight_figure", self, "on_lowlight")
	
	for figure in $Figures.get_children():
		figure.connect("highlight_figure", self, "on_highlight")
		figure.connect("lowlight_figure", self, "on_lowlight")

func setup_chart(chart):
	assert(chart.size() == 15)
	$Chart.set_chart(chart)
	$Figures.set_chart(chart)

func set_info(querent, question, date):
	$InfoPanel.set_querent(querent)
	$InfoPanel.set_question(question)
	$InfoPanel.set_date(date)

func on_highlight(house):
	$Chart.set_highlight(house)
	$Figures.set_highlight(house)

func on_lowlight(house):
	$Chart.set_lowlight(house)
	$Figures.set_lowlight(house)
