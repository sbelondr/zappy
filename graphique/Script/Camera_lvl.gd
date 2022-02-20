extends Camera

var g_move = 0.1

func _process(delta: float) -> void:
	if Input.is_action_pressed("cam_left"):
		var h = get_h_offset()
		set_h_offset(h - g_move)
	if Input.is_action_pressed("cam_right"):
		var h = get_h_offset()
		set_h_offset(h + g_move)
	if Input.is_action_pressed("cam_up"):
		translation.z -= 30 * delta
#		var v = get_v_offset()
#		set_v_offset(v + g_move)
	if Input.is_action_pressed("cam_down"):
		translation.z += 30 * delta
#		var v = get_v_offset()
#		set_v_offset(v - g_move)
	if Input.is_action_just_pressed("zoom"):
		fov = fov - 10
	if Input.is_action_just_pressed("dezoom"):
		fov = fov + 10



# Called when the node enters the scene tree for the first time.
func _ready():
	pass # Replace with function body.
