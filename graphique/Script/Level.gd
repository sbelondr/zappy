extends Spatial

const texture_block: PackedScene = preload("res://Texture/block.tscn")
const trantorien: PackedScene = preload("res://Texture/Trantorien.tscn")

# get egg texture
const egg: PackedScene = preload("res://Texture/Egg.tscn");

# base map
var g_x: int = 10
var g_z: int = 10
var map = []

# time unit
var TIME: float = 1

# global variable for the socket
const HOST: String = "localhost"
const PORT: int = 8080
const RECONNECT_TIMEOUT: float = 3.0
const Client = preload("res://Script/Client.gd")
var _client: Client = Client.new()

# list
var list_player = Dictionary()
var list_team = Dictionary()
var list_egg = Dictionary()

enum TEAM {
	COLOR
	TREE_ID
}

enum EGG {
	OBJ,
	VEC,
	JOUEUR
}

# HUD
onready var tree = $HUD/Tree
var root_tree;

# color teams for the HUD
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

var generate_name = load("res://Script/GenerateName.gd").new()

# add block
# Args:
# 	texture: texture block
#	vec: position
# Return: obj
func add_block(texture, vec: Vector3, scale=Vector3(0,0,0)):
	var obj = texture.instance()
	obj.translation = vec
	if scale.x != 0:
		obj.scale = scale
	$Terrain.add_child(obj, true)
	return obj

func create_map() -> void:
	var y := 0
	for x in g_x:
		map.append(Array())
		for z in g_z:
			map[x].append(add_block(texture_block, Vector3(x, y, z)))

func add_team_hud(name: String) -> TreeItem:
	$HUD/Panel/VBoxContainer/teams.bbcode_text += "\n[color=" + color[cnt_color % 7] + "]" + name + "[/color]"
	var child1: TreeItem = tree.create_item(root_tree)
	cnt_color += 1
	child1.set_text(0, name)
	return child1

# Args:
#	name: name for Trantorien
#	vec: Vector to indicate the position of Trantorien
# add new Trantorien
func add_trantorien(id_trantorien: String, vec: Vector3, orientation: int, level: int, teams: String) -> void:
	var obj = add_block(trantorien, vec, Vector3(0.1, 0.1, 0.1))
	list_player[id_trantorien] = obj
	var name = generate_names()
	obj.set_trantorien(name, id_trantorien, teams, orientation, level)
	obj.manage_orientation_trantorien(orientation, TIME)
	# add user in HUD
	if teams in list_team:
		var subchild1 = tree.create_item(list_team[teams])
		subchild1.set_text(0, id_trantorien)
	$HUD/Panel/VBoxContainer/players.bbcode_text += '\n' + "\n[color=" + color[cnt_color % 7] + "]" + id_trantorien + "[/color]"

# I don't remember but it's interresting
# fuck you
# edit: permet de savoir si on est sur le bord ou non, donc savoir si on utilise
# la fonction interpolate ou non
func is_interpolate(val: float, new_val: float) -> bool:
	if val == new_val or val + 1 == new_val or val - 1 == new_val:
		return true
	return false

# deplace Trantorien
# Args:
#	name: name of Trantorien
#	vec: new position of Trantorien
#	orientation: orientation of Trantorien (1: N, 2: E, 3: S, 4: O)
func move_trantorien(name: String, vec: Vector3, orientation: int) -> void:
	if name in list_player:
		var player = list_player.get(name)
		player.move_trantorien(vec, orientation, TIME)

# remove Trantorien on the map and the list
# Arg:
#	name: name of Trantorien
func die_trantorien(name: String) -> void:
	if name in list_player:
		var obj = list_player[name]
		obj.dead()
		list_player.erase(name)

# remove ressource egg with name
# Arg:
#	name: name of egg
func die_egg(name: String) -> void:
	if name in list_egg:
		var obj = list_egg[name][EGG.OBJ]
		obj.queue_free()
		list_egg.erase(name)

# add gem when bct is send by the server
func add_all_gem(arr) -> void:
	var vec: Vector3 = Vector3(int(arr[1]), 1, int(arr[2]))
	var gems = [int(arr[3]), int(arr[4]), int(arr[5]), int(arr[6]), int(arr[7]), int(arr[8]), int(arr[9])]
	map[vec.x][vec.z].set_inventory(gems)

func player_kicked(id, position):
	var obj_player = list_player[arr[1]]
	obj_player.kick()

func _process(_delta):
	if Input.is_action_just_pressed("+"):
		if TIME > 0.21:
			TIME -= 0.2
#			launch_timer()
	if Input.is_action_just_pressed("-"):
		TIME += 0.2
	if Input.is_action_just_pressed("quit"):
		get_tree().quit()
	if Input.is_action_just_pressed("reload"):
# warning-ignore:return_value_discarded
		get_tree().reload_current_scene()

# Manage connection server

func _ready():
	# manage connection socket
	add_child(_client)
# warning-ignore:return_value_discarded
	_client.connect("connected", self, "_handle_client_connected")
# warning-ignore:return_value_discarded
	_client.connect("disconnected", self, "_handle_client_disconnected")
# warning-ignore:return_value_discarded
	_client.connect("data", self, "_handle_client_data")
# warning-ignore:return_value_discarded
	_client.connect("error", self, "_handle_client_error")
	_client.connect_to_server(HOST, PORT)
	root_tree = tree.create_item()
	$HUD/Tree.set_hide_root(true)

func _handle_client_connected() -> void:
	print("Client connected to server.")
	_client.send_var("GRAPHIC")

func _handle_client_data(data: PoolByteArray) -> void:
	var msg := data.get_string_from_utf8().split('\n')
	for line in msg:
		var arr : Array = line.split(' ')
		command_server(arr)

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

# Signal

func _on_Tree_item_deselected(_id) -> void:
	for player in list_player:
		list_player[player].highlight_end()

func _on_Tree_item_selected(id) -> void:
	if not id in list_player:
		return
	$Camera.current = false
	for player in list_player:
		if player != id:
			list_player[player].highlight_end()
	var status = list_player[id].highlight()
	if not status:
		$Camera.make_current()
