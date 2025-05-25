extends Resource
class_name Player

var name: String
var color: Color
var score: int = 0

func _init(_name: String, _color: Color):
	name = _name
	color = _color
	score = 0
