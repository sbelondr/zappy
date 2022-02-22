extends Spatial

var level: int = 1

var inventory: Array = [0, 0, 0, 0, 0, 0, 0]

onready var inventory_node := [
	get_node('NodeHUD/HUDPlayer/info_player/GC_inventaire/Food'),
	get_node('NodeHUD/HUDPlayer/info_player/GC_inventaire/Linemate'),
	get_node('NodeHUD/HUDPlayer/info_player/GC_inventaire/Deraumere'),
	get_node('NodeHUD/HUDPlayer/info_player/GC_inventaire/Sibur'),
	get_node('NodeHUD/HUDPlayer/info_player/GC_inventaire/Mendiane'),
	get_node('NodeHUD/HUDPlayer/info_player/GC_inventaire/Phiras'),
	get_node('NodeHUD/HUDPlayer/info_player/GC_inventaire/Thystame')
]

onready var camera_trantorien = $Camera #get_node("Control/ViewportContainer/Viewport/Camera")

var current_rotation : float
var goal_rotation : float
var rotation_speed : float
var rotation_progress : float

var speed : float
var highlighted: bool
var player_id: String
var player_name: String
var orientation: int
var team: String

onready var animPlayer : AnimationPlayer = get_node("AnimationPlayer")
onready var tween : Tween = get_node("Tween")

signal selected(player)

func set_trantorien(pname: String, pid, pteam: String, porientation: int, plevel: int):
	player_name = pname
	player_id = pid
	team = pteam
	orientation = porientation
	set_level(plevel)
	get_node("NodeHUD/HUDPlayer/info_player/GC_player/lab_id").text = pid
	get_node("NodeHUD/HUDPlayer/info_player/GC_player/lab_name").text = pname
	get_node("NodeHUD/HUDPlayer/info_player/GC_player/lab_team").text = pteam
	

#Much better than using attributes as globals, PLEASE CALL THIS
func set_level(new_level: int) -> void:
	level = new_level
	get_node("NodeHUD/HUDPlayer/info_player/GC_player/lab_level").text = str(new_level)
	get_node("NodeHUD/HUDPlayer/info_player/pb_level").value = new_level

#Much better than using attributes as globals, PLEASE CALL THIS
func set_inventory(new_inventory: Array) -> void:
	inventory[0] = int(new_inventory[0])
	inventory[1] = int(new_inventory[1])
	inventory[2] = int(new_inventory[2])
	inventory[3] = int(new_inventory[3])
	inventory[4] = int(new_inventory[4])
	inventory[5] = int(new_inventory[5])
	inventory[6] = int(new_inventory[6])
#	inventory = new_inventory
	load_inventory_hud()

# i don't remember but it's interresting
# fuck you
func is_interpolate(val: int, new_val: int) -> bool:
	if val == new_val or val + 1 == new_val or val - 1 == new_val:
		return true
	return false

func manage_orientation_trantorien(orientation_trantorien: int, time: float):
	if (orientation_trantorien == 1):
		rotation_trantorien(180, time);
	elif (orientation_trantorien == 2):
		rotation_trantorien(90, time);
	elif (orientation_trantorien == 3):
		rotation_trantorien(0, time);
	elif (orientation_trantorien == 4):
		rotation_trantorien(270, time);

#Move trantorien to target direction, speed is TIME
#Handles animation and tweening, PLEASE CALL THIS
func move_trantorien(dest: Vector3, orientation: int, time: float) -> void:
	manage_orientation_trantorien(orientation, TIME)
	if is_interpolate(translation.x, dest.x) \
		and is_interpolate(translation.y, dest.y) \
		and is_interpolate(translation.z, dest.z):
	# warning-ignore:return_value_discarded
		tween.interpolate_property(self, "translation", translation, dest, time, Tween.TRANS_CUBIC)
	# warning-ignore:return_value_discarded
		tween.start()
		animPlayer.queue("WalkCycle")
	else:
		translation = vec

func rotation_trantorien(dest: int, time: float) -> void:
	goal_rotation = deg2rad(dest)
	current_rotation = rotation.y
	rotation_speed = max(time, 0.001)
	rotation_progress = 0

#Handle fork animation and fade into fork loop, PLEASE CALL THIS
func fork_start() -> void:
	animPlayer.queue("Ponte")

#Handles animation end, PLEASE CALL THIS
func fork_end() -> void:
	animPlayer.play_backwards("Ponte")

#Take an item from the ground (no check done)
#Handle animation and all, PLEASE CALL THIS
func pickup(item_id: int) -> void:
	animPlayer.queue("Pickup")
	inventory[item_id] += 1
	inventory_node[item_id].text = str(inventory[item_id])

#Put an item on the ground (no check done)
#Handle animation and all, PLEASE CALL THIS
func putdown(item_id: int) -> void:
	animPlayer.play_backwards("Pickup")
	inventory[item_id] -= 1
	inventory_node[item_id].text = str(inventory[item_id])

#Start ritual animation
#Play a different animation for each level, PLEASE CALL THIS
func start_incantation() -> void:
	var ritual_level := level
	if level > 4:
		ritual_level = 4
	animPlayer.queue("Ritual%d" % ritual_level)

#Play the kick animation
#JUST CALL THIS PLEASE
func kick() -> void:
	animPlayer.queue("Kick")
	
#Is being kicked
#Stop current animation (will play one later) and handle movement, PLEASE CALL THIS
func kicked(new_position: Vector3, time: float) -> void:
# warning-ignore:return_value_discarded
	tween.interpolate_property(self, "translation", null, new_position, time, Tween.TRANS_CUBIC)
# warning-ignore:return_value_discarded
	tween.start()
	animPlayer.stop()

#Play the death animation
#Handle deleting the character AFTER the animation finished, PLEASE CALL THIS
func dead() -> void:
	animPlayer.queue("Death")
# warning-ignore:return_value_discarded
	animPlayer.connect("animation_finished", self, "_death_animation_finished")

#Play the idle animation when nothing else is going on
#Necessary to avoid doing stupid thing, also its a placeholder. PLEASE CALL THIS
func idle() -> void:
	animPlayer.queue("Pose")

func load_inventory_hud():
	for i in len(inventory_node):
		inventory_node[i].text = str(inventory[i])

func broadcast(msg: String):
	get_node("Viewport/Panel/Label").text = msg
	var node_panel = get_node("Viewport/Panel")
	node_panel.visible = true
	node_panel.rect_size.x = len(msg) * 30
	get_node("Viewport").size.x = (len(msg) * 30) + 10
	$Timer_broadcast.start(5.0)

func highlight():
	if not highlighted:
		highlighted = true
		scale *= 2
		camera_trantorien.visible = true
		camera_trantorien.make_current()
		get_node("NodeHUD/HUDPlayer/info_player").visible = true
		return true
	else:
		highlight_end()
		return false

func highlight_end():
	if highlighted:
		highlighted = false
		scale /= 2
		camera_trantorien.current = false
#		get_node('NodeHUD/HUDPlayer/GC_inventaire').visible = false
		get_node("NodeHUD/HUDPlayer/info_player").visible = false

func _ready():
	animPlayer.get_animation("WalkCycle").set_loop(true)
	animPlayer.get_animation("Ritual1").set_loop(true)
	animPlayer.get_animation("Ritual2").set_loop(true)
	animPlayer.get_animation("Ritual3").set_loop(true)
	animPlayer.get_animation("Ritual4").set_loop(true)
	animPlayer.get_animation("Pose").set_loop(true)
	animPlayer.get_animation("Ponte loop").set_loop(true)
	current_rotation = rotation.y
	goal_rotation = current_rotation
	rotation_progress = 0
	rotation_speed = 0.1
	orientation = 0
	team = ''
	player_id = ''
	highlighted = false
	animPlayer.play("Idle")
#	get_node('NodeHUD/HUDPlayer/info_player/GC_inventaire').visible = false
	get_node("NodeHUD/HUDPlayer/info_player").visible = false
	get_node("Viewport/Panel").visible = false
	load_inventory_hud()
#		NodeHUD/HUDPlayer/GC_inventaire/Food
	
#Private function, PLEASE DO *NOT* CALL THIS
func _death_animation_finished(animation_name: String) -> void:
	if animation_name == "Death":
		queue_free()
	elif animation_name == "Ponte":
		animPlayer.play("Ponte loop")

func _process(delta: float):
	if rotation_progress < 1:
		rotation.y = lerp_angle(current_rotation, goal_rotation, min(1, rotation_progress))
		rotation_progress += (1 / rotation_speed) * delta

func _on_input_event(_camera, event, _position, _normal, _shape_idx):
	if event is InputEventMouseButton:
		if event.button_index == BUTTON_LEFT:# and event.pressed:
			emit_signal("selected", self)

func _on_Timer_broadcast_timeout():
	get_node("Viewport/Panel").visible = false
