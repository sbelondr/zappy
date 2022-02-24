extends Spatial

# list
var list_player = Dictionary()
var list_team = Dictionary()
var list_egg = Dictionary()

enum EGG {
	OBJ,
	VEC,
	JOUEUR
}

# map
var g_x: int = 10
var g_z: int = 10

var map := []

# Texture

const texture_block: PackedScene = preload("res://Texture/block.tscn")
const trantorien: PackedScene = preload("res://Texture/Trantorien.tscn")
const egg: PackedScene = preload("res://Texture/Egg.tscn");

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
func add_block(texture : PackedScene, vec: Vector3, scale=Vector3(0,0,0)):
	var obj = texture.instance()
	obj.translation = vec
	if scale.x != 0:
		obj.scale = scale
	$Terrain.add_child(obj, true)
	return obj

func player_putdown_item(id_player: int, color_gem: int):
	if id_player in list_player:
		var player = list_player[id_player]
		var vec_player = player.translation
		player.putdown(color_gem)
		map[vec_player.x][vec_player.z].add_item(color_gem)

func player_pickup_item(id_player: String, color_gem: int):
	if id_player in list_player:
		var player = list_player[id_player]
		var vec_player = player.translation
		player.pickup(color_gem)
		map[vec_player.x][vec_player.z].remove_item(color_gem)

func player_fork_start(id_player: String):
	if id_player in list_player:
		list_player[id_player].fork_start()

# set map
# Args:
#	g_x: size x
#	g_y: size y
# Return: new map
func _set_map(x: int, z: int):
	g_x = x
	g_z = z
	var y := 0
	for x in g_x:
		map.append(Array())
		for z in g_z:
			map[x].append(add_block(texture_block, Vector3(x, y, z)))

# set camera
# Args:
#	g_x: size x
#	g_y: size y
func _set_camera() -> void:
	get_node("Camera").h_offset = g_x / 2.0
	get_node("Camera").v_offset = g_z / 2.0
	get_node("Camera").fov = g_x * 2.0

# set map and camera
# Args:
#	g_x: size x
#	g_y: size y
# Return: new map
func set_map_and_camera(x: int, z: int):
	_set_map(x, z)
	_set_camera()

func message_server(msg: String) -> void:
	$HUD/logs.text = "Message server: " + msg

func game_over(name_team: String) -> void:
	$End/GameOver.get_node("team_win").text(name_team + " win !")
	$End/GameOver.visible = true

func add_team_hud(id_team: String) -> void:
	$HUD/Panel/VBoxContainer/teams.bbcode_text += "\n[color=" + \
			color[cnt_color % 7] + "]" + id_team + "[/color]"
	var child1: TreeItem = tree.create_item(root_tree)
	cnt_color += 1
	child1.set_text(0, id_team)
	list_team[id_team] = child1

# Add user in the tree HUD
# Args:
#	teams: team of player
#	id_trantorien: new player to add
func _add_player_in_hud(team: String, id_trantorien: String) -> void:
	var obj_team = list_team[team]
	var subchild1 = tree.create_item(obj_team)
	subchild1.set_text(0, id_trantorien)
	$HUD/Panel/VBoxContainer/players.bbcode_text += '\n' + "\n[color=" \
			+ color[cnt_color % 7] + "]" + id_trantorien + "[/color]"

# Args:
#	name: name for Trantorien
#	vec: Vector to indicate the position of Trantorien
# add new Trantorien
func add_trantorien(id_trantorien: String, vec: Vector3, orientation: String, \
		level: int, team: String, time: float):
	var obj = add_block(trantorien, vec, Vector3(0.1, 0.1, 0.1))
	var name = generate_name.generate_names()
	obj.set_trantorien(name, id_trantorien, team, orientation, level)
	obj.manage_orientation_trantorien(orientation, time)
	return obj

func add_new_player(id_player: String, position: Vector3, orientation: String, \
		level: int, team: String, time: float):
	var obj_team = list_team[team]
	list_player[id_player] = add_trantorien(id_player, \
			position, orientation, level, team, time)
	# add user in HUD
	_add_player_in_hud(team, id_player)
	client.send_var("pin " + id_player)

# deplace Trantorien
# Args:
#	name: name of Trantorien
#	vec: new position of Trantorien
#	orientation: orientation of Trantorien (1: N, 2: E, 3: S, 4: O)
func move_trantorien(id_player, vec: Vector3, orientation: String, time: float) -> void:
	if id_player in list_player:
		var player = list_player[id_player]
		player.move_trantorien(vec, orientation, time)

# remove Trantorien on the map and the list
# Arg:
#	name: name of Trantorien
func player_die(id_player: String) -> void:
	if id_player in list_player:
		var player = list_player[id_player]
		player.dead()
		list_player.erase(id_player)

func player_incantation(arr_player: Array) -> void:
	var len_arr = len(arr_player)
	while i < len_arr:
		if arr_player[i] in list_player and list_player[arr_player[i]]:
			var player = list_player[arr_player[i]]
			player.start_incantation()
		i += 1

func spawn_egg(id_egg: String, id_player: String, position: Vector3):
	if id_player in list_player:
		list_player[id_player].fork_end()
		var new_egg = add_block(id_egg, position)
		list_egg[id_egg] = [new_egg, position, id_player]

# remove ressource egg with name
# Arg:
#	name: name of egg
func die_egg(id_egg: String) -> void:
	if id_egg in list_egg:
		var egg = list_egg[id_egg][EGG.OBJ]
		egg.queue_free()
		list_egg.erase(id_egg)

# add gem when bct is send by the server
func add_all_gem(arr: Array) -> void:
	var vec: Vector3 = Vector3(int(arr[1]), 1, int(arr[2]))
	var gems = [int(arr[3]), int(arr[4]), int(arr[5]), int(arr[6]), \
			int(arr[7]), int(arr[8]), int(arr[9])]
	map[vec.x][vec.z].set_inventory(gems)

func player_broadcast(id_player, msg) -> void:
	if id_player in list_player:
		list_player[id_player].broadcast(msg)

func player_level(id_player: String, level: int):
	var player = list_player[id_player]
	player.set_level(level)

func player_set_inventory(id_player: String, inventory: Array):
	if id_player in list_player:
		list_player[id_player].set_inventory(inventory)


func player_kicked(id_player):
	var player = list_player[id_player]
	player.kick()

func _ready():
	root_tree = tree.create_item()
	$HUD/Tree.set_hide_root(true)

# Signal

func _on_Tree_item_deselected(_id) -> void:
	pass
	#for player in list_player:
	#	list_player[player].highlight_end()

func _on_Tree_item_selected(id) -> void:
	pass
	#if not id in list_player:
	#	return
	#$Camera.current = false
	#for player in list_player:
	#	if player != id:
	#		list_player[player].highlight_end()
	#var status = list_player[id].highlight()
	#if not status:
	#	$Camera.make_current()
