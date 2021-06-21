extends Reference

const HOUSE  = "House"
const SHIELD = "Shield"

enum Method {
	AUTOMATIC, SELECTION, MANUAL
}

var querent_name
var question_text
var chart_type
var house_number
var generation_method
var date_time
var figure_array

func set_house_chart():
	chart_type = HOUSE

func is_house_chart():
	return chart_type == HOUSE

func set_shield_chart():
	chart_type = SHIELD

func is_shield_chart():
	return chart_type == SHIELD

func set_house_number(n):
	assert(n > 0 and n < 13)
	house_number = n

func set_automatic():
	generation_method = Method.AUTOMATIC

func set_selection():
	generation_method = Method.SELECTION

func set_manual():
	generation_method = Method.MANUAL

func set_current_time():
	date_time = OS.get_datetime()
