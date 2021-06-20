extends Control

func _ready():
	for figure in $Chart.get_children():
		figure.connect("highlight_figure", self, "on_highlight")
		figure.connect("lowlight_figure", self, "on_lowlight")
	
	for figure in $Figures/Container.get_children():
		figure.connect("highlight_figure", self, "on_highlight")
		figure.connect("lowlight_figure", self, "on_lowlight")
	
	$Figures.highlight_similar(true)

func setup_chart(chart):
	assert(chart.size() == 15)
	$Chart.set_chart(chart)
	$Figures.set_chart(chart)

func set_info(querent, question, date):
	$InfoPanel.set_querent(querent)
	$InfoPanel.set_question(question)
	$InfoPanel.set_date(date)

func on_highlight(house):
	$Chart.on_highlight(house)
	$Figures.on_highlight(house)

func on_lowlight(house):
	$Chart.on_lowlight(house)
	$Figures.on_lowlight(house)
