extends Node2D

@export var left_action: Key
@export var right_action: Key
@export var speed: float = 150
@export var turn_speed: float = 3.0
@export var color: Color = Color.WHITE

var angle = 0.0
var trail: Line2D
var playerHead: Vector2 = Vector2(0, 0)

func _ready():
	trail = $Line2D
	trail.default_color = color
	trail.add_point(playerHead)

func _process(delta):
	if Input.is_key_pressed(left_action):
		angle -= turn_speed * delta
	elif Input.is_key_pressed(right_action):
		angle += turn_speed * delta

	var dir = Vector2.RIGHT.rotated(angle)
	playerHead += dir * speed * delta

	trail.add_point(playerHead)
