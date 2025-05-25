extends Node2D

@export var left_action: Key
@export var right_action: Key
@export var speed: float = 150
@export var turn_speed: float = 3.0
@export var color: Color = Color.WHITE

var player_data: Player
var angle: float = 0.0  # custom angle (radians)
var start_position: Vector2  # where the worm logically starts
var trail: Line2D
var last_trail_point: Vector2

const TRAIL_POINT_DISTANCE = 3.0  # Minimum distance before adding a trail point

func _ready():
	trail = $Line2D
	trail.default_color = color

	if start_position == null:
		start_position = Vector2.ZERO  # fallback if not set from outside

	last_trail_point = start_position
	trail.add_point(last_trail_point)

func _process(delta):
	# Update angle based on input
	if Input.is_key_pressed(left_action):
		angle -= turn_speed * delta
	elif Input.is_key_pressed(right_action):
		angle += turn_speed * delta

	# Calculate direction and new head position
	var dir = Vector2.RIGHT.rotated(angle)
	start_position += dir * speed * delta

	# Add trail point only if moved far enough
	if start_position.distance_to(last_trail_point) >= TRAIL_POINT_DISTANCE:
		trail.add_point(start_position)
		last_trail_point = start_position
