extends Spatial

const texture_block: PackedScene = preload("res://Texture/block.tscn")
const trantorien: PackedScene = preload("res://Texture/Trantorien.tscn")

# get all gems texture
const array_gem: Array = [
	preload("res://Texture/Gem.tscn"),
	preload("res://Texture/Gem2.tscn"),
	preload("res://Texture/Gem3.tscn"),
	preload("res://Texture/Gem4.tscn"),
	preload("res://Texture/Gem5.tscn"),
	preload("res://Texture/Gem6.tscn"),
	preload("res://Texture/Gem7.tscn")
]

enum GEM {
	BLUE,
	YELLOW,
	RED,
	GREEN,
	ORANGE,
	PINK,
	PURPLE
}

# get egg texture
const egg: PackedScene = preload("res://Texture/Egg.tscn");

# base map
var g_x: int = 10
var g_z: int = 10
var map = []

enum MAP {
	OBJ_BLOCK,
	GEM_BLUE,
	GEM_YELLOW,
	GEM_RED,
	GEM_GREEN,
	GEM_ORANGE,
	GEM_PINK,
	GEM_PURPLE
}

# time unit
var TIME: int = 1

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

# enum for the dictionnaries
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

enum EGG {
	OBJ,
	VEC,
	JOUEUR
}

# HUD
onready var tree = get_node("CanvasLayer/Tree")
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
			map[x].append([add_block(texture_block, Vector3(x, y, z)), [0, null], [0, null], [0, null], [0, null], [0, null], [0, null], [0, null]]);

# add new Trantorien
# Args:
#	name: name for Trantorien
#	vec: Vector to indicate the position of Trantorien
func add_trantorien(name: String, vec: Vector3, orientation: int, level: int, teams: String) -> void:
	var obj = add_block(trantorien, vec)
	list_player[name] = [obj, vec, orientation, level, teams]
	var subchild1 = tree.create_item(list_team[teams])
	subchild1.set_text(0, name)

# i don't remember but it's interresting
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

# remove ressource egg with name
func die_egg(name: String) -> void:
	if name in list_egg:
		var obj = list_egg[name][EGG.OBJ]
		obj.queue_free()
		list_egg.erase(name)

# calc scale for the gems
func calc_scale(q: float):
	if q > 9:
		q = 9
	q /= 100
	q *= 2
	return Vector3(q, q, q)

func insert_result_map(vec: Vector3, nb_gems: float, color_gem: int, map_gem: int):
	var scale = calc_scale(nb_gems)
	map[vec.x][vec.z][map_gem][0] = nb_gems
	map[vec.x][vec.z][map_gem][1] =	add_block(array_gem[color_gem], vec, scale)

# add gem when bct is send by the server
func add_all_gem(arr):
	var vec: Vector3 = Vector3(int(arr[1]), 1, int(arr[2]))
	if (int(arr[3]) > 0):
		var nb_gems = float(arr[3])
		insert_result_map(vec, nb_gems, GEM.BLUE, MAP.GEM_BLUE)
	if (int(arr[4]) > 0):
		var nb_gems = int(arr[4])
		insert_result_map(vec, nb_gems, GEM.YELLOW, MAP.GEM_YELLOW)
	if (int(arr[5]) > 0):
		var nb_gems = int(arr[5])
		insert_result_map(vec, nb_gems, GEM.RED, MAP.GEM_RED)
	if (int(arr[6]) > 0):
		var nb_gems = int(arr[6])
		insert_result_map(vec, nb_gems, GEM.GREEN, MAP.GEM_GREEN)
	if (int(arr[7]) > 0):
		var nb_gems = int(arr[7])
		insert_result_map(vec, nb_gems, GEM.ORANGE, MAP.GEM_ORANGE)
	if (int(arr[8]) > 0):
		var nb_gems = int(arr[8])
		insert_result_map(vec, nb_gems, GEM.PINK, MAP.GEM_PINK)
	if (int(arr[9]) > 0):
		var nb_gems = int(arr[9])
		insert_result_map(vec, nb_gems, GEM.PURPLE, MAP.GEM_PURPLE)

# useless
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
#	if Input.is_action_just_pressed("debug"):
#		add_block(gem, Vector3(5, 1, 5))
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
			#"ppo #n X Y O\n"
			move_trantorien(arr[1], Vector3(int(arr[2]), 1, int(arr[3])))
		# set time
		elif arr[0] == 'sgt':
			TIME = 1.0 / int(arr[1])
		# add gem
		elif arr[0] == 'bct':
			add_all_gem(arr)
		# add team in HUD
		elif arr[0] == 'tna':
			$CanvasLayer/Panel/VBoxContainer/teams.bbcode_text += "\n[color=" + color[cnt_color % 7] + "]" + arr[1] + "[/color]"
			var child1 = tree.create_item(root_tree)
			child1.set_text(0, arr[1])
#			var subchild1 = tree.create_item(child1)
#			subchild1.set_text(0, "test")
			list_team[arr[1]] = child1
			cnt_color += 1
		# un joueur fait un broadcast
		elif arr[0] == 'pbc':
			pass
		# lance incantation
		elif arr[0] == 'pic':
			pass
		# Fin de l’incantation sur la case donnée avec le résultat R
		elif arr[0] == 'pie':
			pass
		# Le joueur est mort de faim.
		elif arr[0] == 'pdi':
			die_trantorien(arr[1])
		# le joueur jette une ressource
		elif arr[0] == 'pdr':
			if arr[1] in list_player:
				var vec_player = list_player[arr[1]][TRANTORIEN.VEC]
				add_block(array_gem[int(arr[2])], vec_player)
		# le joueur prend une ressource
		elif arr[0] == 'pgt':
			pass
		# Le joueur pond un œuf.
		elif arr[0] == 'pfk':
			# animation
			pass
		# loeuf a ete pondu
		elif arr[0] == 'enw':
			# enw #e #n X Y
			# fin animation
			if arr[2] in list_player:
				var vec_player = list_player[arr[2]][TRANTORIEN.VEC]
				var obj = add_block(egg, vec_player);
				list_egg[arr[1]] = [obj, vec_player, arr[2]]
		# loeuf eclot
		elif arr[0] == 'eht':
			# animation eclosion
			die_egg(arr[1])
			pass
		# joueur connecte pour l'oeuf
		elif arr[0] == 'ebo':
			pass
		# l'oeuf est mort
		elif arr[0] == 'edi':
			die_egg(arr[1])
		# fin du jeu
		elif arr[0] == 'seg':
			get_tree().change_scene("res://Scene/GameOver.tscn")
		# message serveur
		elif arr[0] == 'smg':
			pass
		
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
