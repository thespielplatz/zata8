extends Node2D

@onready var player1 = $Player1
@onready var player2 = $Player2

func _ready():
	player1.global_position = Vector2(200, 300)
	player1.left_action = KEY_Q
	player1.right_action = KEY_W

	player2.global_position = Vector2(600, 300)
	player2.left_action = KEY_O
	player2.right_action = KEY_P
