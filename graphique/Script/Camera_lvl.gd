extends Camera

var g_move = 0.3

func _process(delta: float) -> void:
	if not Manager.line_edit_cheat_enabled:
		if Input.is_action_pressed("cam_left"):
			var h = get_h_offset()
			set_h_offset(h - g_move)
		if Input.is_action_pressed("cam_right"):
			var h = get_h_offset()
			set_h_offset(h + g_move)
		if Input.is_action_pressed("cam_up"):
			translation.z -= 30 * delta
		if Input.is_action_pressed("cam_down"):
			translation.z += 30 * delta
		if Input.is_action_just_pressed("zoom"):
			fov = fov - 10
		if Input.is_action_just_pressed("dezoom"):
			fov = fov + 10
		if Input.is_action_just_pressed("cheat"):
			Manager.line_edit_cheat_enabled = true
		if Input.is_action_just_pressed("hud"):
			Manager.hide_hud = !Manager.hide_hud



# Called when the node enters the scene tree for the first time.
func _ready():
	pass # Replace with function body.
