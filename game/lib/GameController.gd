# res://GameController.gd
extends Node

@export var player_names := ["Alice", "Bob", "Charlie", "Dana"]
@export var colors := [Color.RED, Color.BLUE, Color.GREEN, Color.YELLOW]
@export var game_area: Node

var players: Array[Player] = []
var score_to_win: int

func _ready():
	_create_players()
	score_to_win = (players.size() - 1) * 10
	print("Score to win: ", score_to_win)
	_start_round()

func _create_players():
	players.clear()
	for i in range(player_names.size()):
		var p = Player.new(player_names[i], colors[i])
		players.append(p)

func _start_round():
	game_area.clear_worms()

	for player in players:
		game_area.add_worm(player)
