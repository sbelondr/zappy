extends Spatial

const texture_block: PackedScene = preload("res://Texture/block.tscn")
const trantorien: PackedScene = preload("res://Texture/Trantorien.tscn")
const gem: PackedScene = preload("res://Texture/Gem.tscn")
const gem2: PackedScene = preload("res://Texture/Gem2.tscn")
const gem3: PackedScene = preload("res://Texture/Gem3.tscn")
const gem4: PackedScene = preload("res://Texture/Gem4.tscn")
const gem5: PackedScene = preload("res://Texture/Gem5.tscn")
const gem6: PackedScene = preload("res://Texture/Gem6.tscn")
const gem7: PackedScene = preload("res://Texture/Gem7.tscn")
var g_x: int = 10
var g_z: int = 10

var TIME: int = 1

# scoket global variable
const HOST: String = "localhost"
const PORT: int = 8080
const RECONNECT_TIMEOUT: float = 3.0
const Client = preload("res://Script/Client.gd")
var _client: Client = Client.new()

var list_player = Dictionary()
var list_team = Dictionary()

onready var tree = get_node("CanvasLayer/Tree")
var root_tree;

# color teams
var cnt_color = 0
const color: Array = [
	'blue',
	'red',
	'yellow',
	'purple',
	'orange',
	'gray',
	'white'
]

enum TRANTORIEN {
	OBJ,
	VEC,
	ORIENTATION,
	LEVEL,
	TEAMS
}

enum TEAM {
	COLOR
	TREE_ID
}

# add block
# Args:
# 	texture: texture block
#	vec: position
# Return: obj
func add_block(texture, vec: Vector3):
	var obj = texture.instance()
	obj.translation = vec
	$Terrain.add_child(obj, true)
	return obj

func create_map() -> void:
	var y := 0
	for x in g_x:
		for z in g_z:
			add_block(texture_block, Vector3(x, y, z))

# add new Trantorien
# Args:
#	name: name for Trantorien
#	vec: Vector to indicate the position of Trantorien
func add_trantorien(name: String, vec: Vector3, orientation: int, level: int, teams: String) -> void:
	var obj = add_block(trantorien, vec)
	list_player[name] = [obj, vec, orientation, level, teams]
	print (list_team[teams])
	print(name)
	var subchild1 = tree.create_item(list_team[teams])
	subchild1.set_text(0, name)

func is_interpolate(val: int, new_val: int) -> bool:
	if val == new_val or val + 1 == new_val or val - 1 == new_val:
		return true
	return false

# deplace Trantorien
# Args:
#	name: name of Trantorien
#	vec: new position of Trantorien
func move_trantorien(name: String, vec: Vector3) -> void:
	if name in list_player:
		var player = list_player.get(name)
		var obj = player[TRANTORIEN.OBJ]
#		obj.translation = vec
		if is_interpolate(obj.translation.x, vec.x) and is_interpolate(obj.translation.y, vec.y) \
			and is_interpolate(obj.translation.z, vec.z):
			$Tween.interpolate_property(obj, "translation", obj.translation, vec, TIME, Tween.TRANS_CUBIC)
			$Tween.start()
		else:
			obj.translation = vec

# remove Trantorien on the map and the list
# Arg:
#	name: name of Trantorien
func die_trantorien(name: String) -> void:
	if name in list_player:
		var obj = list_player[name][TRANTORIEN.OBJ]
		obj.queue_free()
		list_player.erase(name)

func _on_Timer_timeout():
	pass
#	var vec : Vector3 = list_player["coucou"][1]
#	vec.x += 1
#	vec.z += 1
#	list_player["coucou"][1] = vec
#	if vec.x < g_x:
#		move_trantorien("coucou", vec)
#	else:
#		$Timer.stop()
#		die_trantorien("coucou")

func launch_timer():
	$Timer.wait_time = TIME
	$Timer.start()

func _physics_process(delta):
	if Input.is_action_just_pressed("+"):
		if TIME > 0.21:
			TIME -= 0.2
			launch_timer()
	if Input.is_action_just_pressed("-"):
		TIME += 0.2
		launch_timer()
	if Input.is_action_just_pressed("debug"):
		add_block(gem, Vector3(5, 1, 5))
	if Input.is_action_just_pressed("quit"):
		get_tree().quit()
	$CanvasLayer/CameraPos.text = "get_viewport().get_rect().size.x:" + String(OS.get_real_window_size()) + \
		", x: " + String($Camera.translation.x) + ", y: " + String($Camera.translation.y) + \
		", z: " + String($Camera.translation.z) + ", h: " + String($Camera.get_h_offset()) + ", v:" + String($Camera.get_v_offset()) + ", fov:" + String($Camera.fov)

func _ready():
	# launch_timer()
	# manage connection socket
	add_child(_client)
	_client.connect("connected", self, "_handle_client_connected")
	_client.connect("disconnected", self, "_handle_client_disconnected")
	_client.connect("data", self, "_handle_client_data")
	_client.connect("error", self, "_handle_client_error")
	_client.connect_to_server(HOST, PORT)
	root_tree = tree.create_item()
	tree.set_hide_root(true)

func _handle_client_connected() -> void:
	print("Client connected to server.")
	_client.send_var("GRAPHIC")

func _handle_client_data(data: PoolByteArray) -> void:
	var msg := data.get_string_from_utf8().split('\n')
	for line in msg:
		$CanvasLayer/logs.text += '\n' + line
		var arr : Array = line.split(' ')
		# generate map
		if arr[0] == "msz":
			print('map')
			g_x = int(arr[1])
			g_z = int(arr[2])
			var camera_script = preload("res://Script/Camera_lvl.gd")
			get_node("Camera").h_offset = g_x / 2
			get_node("Camera").v_offset = g_z / 2
			get_node("Camera").fov = g_x * 2
			create_map()
		# new player
		elif arr[0] == 'pnw':
			# pnw #n X Y O L N
			print('new player: ' + arr[6])
			if arr[6] != 'GRAPHIC' and arr[6] != '(null)':
				add_trantorien(arr[1], Vector3(int(arr[2]), 1, int(arr[3])), int(arr[4]), int(arr[5]), arr[6])
				$CanvasLayer/Panel/VBoxContainer/players.bbcode_text += '\n' + "\n[color=" + color[cnt_color % 7] + "]" + arr[1] + "[/color]"
		# move player
		elif arr[0] == 'ppo':
			print('position')
			#"ppo #n X Y O\n"
			move_trantorien(arr[1], Vector3(int(arr[2]), 1, int(arr[3])))
		# set time
		elif arr[0] == 'sgt':
			TIME = 1.0 / int(arr[1])
		# add gem
		elif arr[0] == 'bct':
			if (int(arr[3]) > 0):
				add_block(gem, Vector3(int(arr[1]), 1, int(arr[2])))
			if (int(arr[4]) > 0):
				add_block(gem2, Vector3(int(arr[1]), 1, int(arr[2])))
			if (int(arr[5]) > 0):
				add_block(gem3, Vector3(int(arr[1]), 1, int(arr[2])))
			if (int(arr[6]) > 0):
				add_block(gem4, Vector3(int(arr[1]), 1, int(arr[2])))
			if (int(arr[7]) > 0):
				add_block(gem5, Vector3(int(arr[1]), 1, int(arr[2])))
			if (int(arr[8]) > 0):
				add_block(gem6, Vector3(int(arr[1]), 1, int(arr[2])))
			if (int(arr[9]) > 0):
				add_block(gem7, Vector3(int(arr[1]), 1, int(arr[2])))
		# add team in HUD
		elif arr[0] == 'tna':
			$CanvasLayer/Panel/VBoxContainer/teams.bbcode_text += "\n[color=" + color[cnt_color % 7] + "]" + arr[1] + "[/color]"

			var child1 = tree.create_item(root_tree)
			child1.set_text(0, arr[1])
#			var subchild1 = tree.create_item(child1)
#			subchild1.set_text(0, "test")
			list_team[arr[1]] = child1
			cnt_color += 1
		else:
			print("Commande not set: '%s'" % line)
		

func _connect_after_timeout(timeout: float) -> void:
	yield(get_tree().create_timer(timeout), "timeout")
	_client.connect_to_server(HOST, PORT)

func _handle_client_disconnected() -> void:
	print("Client disconnected from server.")
	_connect_after_timeout(RECONNECT_TIMEOUT)
#
func _handle_client_error() -> void:
	print("Client error.")
	_connect_after_timeout(RECONNECT_TIMEOUT)
