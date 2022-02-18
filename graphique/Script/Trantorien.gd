extends Spatial

var level := 1

const TextInventory := [
	"Food",
	"Linemate",
	"Deraumere",
	"Sibur",
	"Mendiane",
	"Phiras",
	"Thystame"
]

var inventory := [0, 0, 0, 0, 0, 0, 0, 0]

onready var inventory_node := [
	get_node('NodeHUD/HUDPlayer/ItemContainer/Food'),
	get_node('NodeHUD/HUDPlayer/ItemContainer/Linemate'),
	get_node('NodeHUD/HUDPlayer/ItemContainer/Deraumere'),
	get_node('NodeHUD/HUDPlayer/ItemContainer/Sibur'),
	get_node('NodeHUD/HUDPlayer/ItemContainer/Mendiane'),
	get_node('NodeHUD/HUDPlayer/ItemContainer/Phiras'),
	get_node('NodeHUD/HUDPlayer/ItemContainer/Thystame')
]

var current_rotation : float
var goal_rotation : float
var rotation_speed : float
var rotation_progress : float

var speed : float
var highlighted := false

var player_id: String
var orientation: int
var team: String

onready var animPlayer : AnimationPlayer = get_node("AnimationPlayer")
onready var tween : Tween = get_node("Tween")

signal selected(player)

var gem_texture = preload("res://Texture/Gem.tscn");

func set_trantorien(pteam: String, porientation: int, plevel: int):
	team = pteam
	orientation = porientation
	level = plevel

#Much better than using attributes as globals, PLEASE CALL THIS
func set_level(new_level: int) -> void:
	level = new_level
	
#Much better than using attributes as globals, PLEASE CALL THIS
func set_inventory(new_inventory: Array) -> void:
	print("----------------------- ici ---------------------")
	print(new_inventory)
	inventory[0] = int(new_inventory[0])
	inventory[1] = int(new_inventory[1])
	inventory[2] = int(new_inventory[2])
	inventory[3] = int(new_inventory[3])
	inventory[4] = int(new_inventory[4])
	inventory[5] = int(new_inventory[5])
	inventory[6] = int(new_inventory[6])
#	inventory = new_inventory
	print(inventory)
	load_inventory_hud()
	print("----end----")

# i don't remember but it's interresting
# fuck you
func is_interpolate(val: int, new_val: int) -> bool:
	if val == new_val or val + 1 == new_val or val - 1 == new_val:
		return true
	return false

func manage_orientation_trantorien(orientation, time):
	if (orientation == 1):
		rotation_trantorien(180, time);
	elif (orientation == 2):
		rotation_trantorien(90, time);
	elif (orientation == 3):
		rotation_trantorien(0, time);
	elif (orientation == 4):
		rotation_trantorien(270, time);

#Move trantorien to target direction, speed is TIME
#Handles animation and tweening, PLEASE CALL THIS
func move_trantorien(dest: Vector3, speed: float) -> void:
#	Tween.interpolate_property(obj, "translation", obj.translation, vec, TIME, Tween.TRANS_CUBIC)
	tween.interpolate_property(self, "translation", translation, dest, speed, Tween.TRANS_CUBIC)
	tween.start()
	animPlayer.queue("WalkCycle")

func rotation_trantorien(dest: int, speed: float) -> void:
	goal_rotation = deg2rad(dest)
	current_rotation = rotation.y
	rotation_speed = max(speed, 0.001)
	rotation_progress = 0

#Handle fork animation and fade into fork loop, PLEASE CALL THIS
func fork_start() -> void:
	print("IL se fout de ma gueule")
	animPlayer.queue("Ponte")

#Handles animation end, PLEASE CALL THIS
func fork_end() -> void:
	animPlayer.play_backwards("Ponte")

#Take an item from the ground (no check done)
#Handle animation and all, PLEASE CALL THIS
func pickup(item_id: int) -> void:
	animPlayer.queue("Pickup")
	print(inventory)
	inventory[item_id] += 1
	inventory_node[item_id] = TextInventory[item_id] + ": " + str(inventory[item_id])

#Put an item on the ground (no check done)
#Handle animation and all, PLEASE CALL THIS
func putdown(item_id: int) -> void:
	animPlayer.play_backwards("Pickup")
	print(inventory)
	print(item_id)
	inventory[item_id] -= 1
	print(TextInventory[item_id] + ": " + str(inventory[item_id]))
	inventory_node[item_id] = TextInventory[item_id] + ": " + str(inventory[item_id])

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
func kicked(new_position: Vector3, speed: float) -> void:
	tween.interpolate_property(self, "translation", null, new_position, speed, Tween.TRANS_CUBIC)
	tween.start()
	animPlayer.stop()

#Play the death animation
#Handle deleting the character AFTER the animation finished, PLEASE CALL THIS
func dead() -> void:
	animPlayer.queue("Death")
	animPlayer.connect("animation_finished", self, "_death_animation_finished")

#Play the idle animation when nothing else is going on
#Necessary to avoid doing stupid thing, also its a placeholder. PLEASE CALL THIS
func idle() -> void:
	animPlayer.queue("Pose")

func load_inventory_hud():
	for i in len(inventory_node):
		print('here')
		inventory_node[i].text = TextInventory[i] + ": " + str(inventory[i])

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
	animPlayer.play("Idle")
	get_node('NodeHUD/HUDPlayer/ItemContainer').visible = false
	load_inventory_hud()
#		NodeHUD/HUDPlayer/ItemContainer/Food
	
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

func highlight():
	if not highlighted:
		highlighted = true
		scale *= 2
		get_node('NodeHUD/HUDPlayer/ItemContainer').visible = true
		

func highlight_end():
	if highlighted:
		highlighted = false
		scale /= 2
		get_node('NodeHUD/HUDPlayer/ItemContainer').visible = false

func _on_input_event(camera, event, position, normal, shape_idx):
	if event is InputEventMouseButton:
		if event.button_index == BUTTON_LEFT and event.pressed:
			emit_signal("selected", self)
			print("Selected")
