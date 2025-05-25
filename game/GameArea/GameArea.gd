extends Control

const START_POSITION_MARGIN = 200
const START_POSITION_MAX_ATTEMPTS = 200
const START_FORWARD_CLEARANCE = 80

var players = []
var worm_scene = preload("res://Worm/Worm.tscn")

func clear_worms():
	for worm in players:
		worm.queue_free()
	players.clear()

func add_worm(player_data):
	var existing_positions: Array[Vector2] = []
	for worm in players:
		existing_positions.append(worm.start_position)

	var spawn_data = _get_random_position_and_angle(existing_positions)
	var spawn_pos = spawn_data["position"]
	var spawn_angle = spawn_data["angle"]

	var worm = worm_scene.instantiate()
	worm.initialize(player_data, spawn_pos, spawn_angle)
	add_child(worm)
	players.append(worm)

func _get_random_position_and_angle(existing_positions: Array[Vector2]) -> Dictionary:
	var local_x = randf_range(START_POSITION_MARGIN, size.x - START_POSITION_MARGIN)
	var local_y = randf_range(START_POSITION_MARGIN, size.y - START_POSITION_MARGIN)
	var candidate = Vector2(local_x, local_y)
	var angle = 0.0
	var attempt = 0

	while attempt < START_POSITION_MAX_ATTEMPTS:
		angle = randf_range(0, TAU)  # full 360 degrees in radians
		var too_close = false
		for pos in existing_positions:
			if pos.distance_to(candidate) < START_POSITION_MARGIN:
				too_close = true
				break

			var forward_point = candidate + Vector2.RIGHT.rotated(angle) * START_FORWARD_CLEARANCE
			if pos.distance_to(forward_point) < START_POSITION_MARGIN:
				too_close = true
				break

		if not too_close:
			return { "position": candidate, "angle": angle }

		attempt += 1

	push_warning("No safe start position + angle found after %d attempts. Using last candidate anyway." % START_POSITION_MAX_ATTEMPTS)
	return { "position": candidate, "angle": angle }
