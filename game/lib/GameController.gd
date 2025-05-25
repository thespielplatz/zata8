# res://GameController.gd
extends Node

@export var player_names := ["Alice", "Bob", "Charlie", "Dana"]
@export var colors := [Color.RED, Color.BLUE, Color.GREEN, Color.YELLOW]
@export var game_area: Node

var players: Array[Player] = []
var score_to_win: int

func _ready():	
	await get_tree().process_frame	
	_create_players()
	score_to_win = (players.size() - 1) * 10
	print("Score to win: ", score_to_win)
	_start_round()

func _create_players():
	players.clear()

	var player_configs = [
		{ "name": "Player 1", "color": Color.RED,    "left": KEY_1,            "right": KEY_Q,            "isPlaying": true },
		{ "name": "Player 2", "color": Color.BLUE,   "left": KEY_CTRL,         "right": KEY_ALT,          "isPlaying": true },
		{ "name": "Player 3", "color": Color.GREEN,  "left": KEY_M,            "right": KEY_COMMA,    "isPlaying": true },
		{ "name": "Player 4", "color": Color.YELLOW, "left": KEY_LEFT,         "right": KEY_DOWN,         "isPlaying": true },
		{ "name": "Player 5", "color": Color.PURPLE, "left": KEY_KP_DIVIDE,    "right": KEY_KP_MULTIPLY,  "isPlaying": false },
		{ "name": "Player 6", "color": Color.ORANGE, "left": MOUSE_BUTTON_LEFT,      "right": MOUSE_BUTTON_RIGHT,     "isPlaying": false }
	]

	for config in player_configs:
		if config.has("isPlaying") and config["isPlaying"]:
			var player = Player.new(
				config["name"],
				config["color"],
				config["left"],
				config["right"]
			)
			players.append(player)


func _start_round():
	game_area.clear_worms()

	for player in players:
		game_area.add_worm(player)
