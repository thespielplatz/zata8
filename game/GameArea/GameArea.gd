extends Control

var players = []

func _ready():
	var player_scene = load("res://Worm/Worm.tscn")
	var player1 = player_scene.instantiate()
	player1.name = "Player1"
	player1.global_position = Vector2(200, 300)
	player1.left_action = KEY_Q
	player1.right_action = KEY_W
	player1.color = Color.RED
	add_child(player1)
	players.push_back(player1)

	var player2 = player_scene.instantiate()
	player2.name = "Player2"
	player2.color = Color.BLUE
	player2.global_position = Vector2(600, 300)
	player2.left_action = KEY_O
	player2.right_action = KEY_P
	add_child(player2)
	players.push_back(player2)
