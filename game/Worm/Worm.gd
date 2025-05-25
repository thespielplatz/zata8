extends Node2D

@export var left_action: Key
@export var right_action: Key
@export var speed: float = 120
@export var turn_speed: float = 2.0
@export var color: Color = Color.WHITE

var player_data: Player
var angle: float = 0.0
var start_position: Vector2
var trail: Line2D
var last_trail_point: Vector2

const TRAIL_POINT_DISTANCE = 3.0

func initialize(_player_data: Player, _start_pos: Vector2, _start_angle: float):
	player_data = _player_data
	start_position = _start_pos
	angle = _start_angle
	color = player_data.color
	left_action = player_data.left_action
	right_action = player_data.right_action

	trail = $Line2D
	trail.default_color = color

	print("Worm initialized for:", player_data.name)

func _ready():
	last_trail_point = start_position
	trail.add_point(last_trail_point)

func _process(delta):
	# Update angle based on input
	if left_action == MOUSE_BUTTON_LEFT:
		if Input.is_mouse_button_pressed(MOUSE_BUTTON_LEFT):
			angle -= turn_speed * delta
	elif Input.is_key_pressed(left_action):
		angle -= turn_speed * delta
		
	if right_action == MOUSE_BUTTON_RIGHT:
		if Input.is_mouse_button_pressed(MOUSE_BUTTON_RIGHT):
			angle += turn_speed * delta
	elif Input.is_key_pressed(right_action):
		angle += turn_speed * delta

	# Calculate direction and new head position
	var dir = Vector2.RIGHT.rotated(angle)
	start_position += dir * speed * delta

	# Add trail point only if moved far enough
	if start_position.distance_to(last_trail_point) >= TRAIL_POINT_DISTANCE:
		trail.add_point(start_position)
		last_trail_point = start_position
