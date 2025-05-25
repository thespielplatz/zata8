# res://Player.gd
extends Resource
class_name Player

var name: String
var color: Color
var score: int = 0
var left_action: Key
var right_action: Key

func _init(_name: String, _color: Color, _left_action: Key, _right_action: Key):
	name = _name
	color = _color
	score = 0
	left_action = _left_action
	right_action = _right_action
