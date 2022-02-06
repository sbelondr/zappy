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
			map[x].append(add_block(texture_block, Vector3(x, y, z)))

#func test_generate_trantorien(num: int):
#	var vec: Vector3 = Vector3(0,0,0)
#	for i in range(num):
#		var obj = add_block(trantorien, vec, Vector3(0.1, 0.1, 0.1))
#		list_player['#' + str(i)] = [obj, vec, 0, 1, '']
#	pass

# Args:
#	name: name for Trantorien
#	vec: Vector to indicate the position of Trantorien
# add new Trantorien
func add_trantorien(name: String, vec: Vector3, orientation: int, level: int, teams: String) -> void:
#	var scale = calc_scale(5)
#	var obj
#	if name in list_player:
#		var player = list_player[name]
#		player[1] = vec
#		player[2] = orientation
#		player[3] = level
#		player[4] = teams
#		obj = player[0]
#	else:
	var obj = add_block(trantorien, vec, Vector3(0.1, 0.1, 0.1))
	list_player[name] = obj #[obj, vec, orientation, level, teams]
	obj.set_trantorien(teams, orientation, level)
	manage_orientation_trantorien(obj, orientation)
	# add user in HUD
	if teams in list_team:
		var subchild1 = tree.create_item(list_team[teams])
		subchild1.set_text(0, name)

# i don't remember but it's interresting
# fuck you
func is_interpolate(val: int, new_val: int) -> bool:
	if val == new_val or val + 1 == new_val or val - 1 == new_val:
		return true
	return false

func manage_orientation_trantorien(obj, orientation):
	if (orientation == 1):
		obj.rotation_trantorien(180, TIME);
	if (orientation == 2):
		obj.rotation_trantorien(90, TIME);
	if (orientation == 3):
		obj.rotation_trantorien(0, TIME);
	if (orientation == 4):
		obj.rotation_trantorien(270, TIME);

# deplace Trantorien
# Args:
#	name: name of Trantorien
#	vec: new position of Trantorien
func move_trantorien(name: String, vec: Vector3, orientation: int) -> void:
	if name in list_player:
		var player = list_player.get(name)
		manage_orientation_trantorien(player, orientation)
		if is_interpolate(player.translation.x, vec.x) and is_interpolate(player.translation.y, vec.y) \
			and is_interpolate(player.translation.z, vec.z):
			player.move_trantorien(vec, TIME)
		else:
			player.translation = vec

# remove Trantorien on the map and the list
# Arg:
#	name: name of Trantorien
func die_trantorien(name: String) -> void:
	if name in list_player:
		var obj = list_player[name]
		obj.dead()
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
	if q < 0:
		q = 0
	q /= 100
	q *= 2
	return Vector3(q, q, q)

func insert_result_map(vec: Vector3, nb_gems: float, color_gem: int):
	var scale = calc_scale(nb_gems)
	map[vec.x][vec.z].gems[color_gem] = [nb_gems, add_block(array_gem[color_gem], vec, scale)]

# add gem when bct is send by the server
func add_all_gem(arr):
	var vec: Vector3 = Vector3(int(arr[1]), 1, int(arr[2]))
	if (int(arr[3]) > 0):
		var nb_gems = float(arr[3])
		insert_result_map(vec, nb_gems, GEM.BLUE)
	if (int(arr[4]) > 0):
		var nb_gems = int(arr[4])
		insert_result_map(vec, nb_gems, GEM.YELLOW)
	if (int(arr[5]) > 0):
		var nb_gems = int(arr[5])
		insert_result_map(vec, nb_gems, GEM.RED)
	if (int(arr[6]) > 0):
		var nb_gems = int(arr[6])
		insert_result_map(vec, nb_gems, GEM.GREEN)
	if (int(arr[7]) > 0):
		var nb_gems = int(arr[7])
		insert_result_map(vec, nb_gems, GEM.ORANGE)
	if (int(arr[8]) > 0):
		var nb_gems = int(arr[8])
		insert_result_map(vec, nb_gems, GEM.PINK)
	if (int(arr[9]) > 0):
		var nb_gems = int(arr[9])
		insert_result_map(vec, nb_gems, GEM.PURPLE)

func _physics_process(delta):
	if Input.is_action_just_pressed("+"):
		if TIME > 0.21:
			TIME -= 0.2
#			launch_timer()
	if Input.is_action_just_pressed("-"):
		TIME += 0.2
	if Input.is_action_just_pressed("quit"):
		get_tree().quit()
	$CanvasLayer/CameraPos.text = "get_viewport().get_rect().size.x:" + String(OS.get_real_window_size()) + \
		", x: " + String($Camera.translation.x) + ", y: " + String($Camera.translation.y) + \
		", z: " + String($Camera.translation.z) + ", h: " + String($Camera.get_h_offset()) + ", v:" + String($Camera.get_v_offset()) + ", fov:" + String($Camera.fov)

func _ready():
#	test_generate_trantorien(1000)
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
#		$CanvasLayer/logs.text += '\n' + line
		var arr : Array = line.split(' ')
		# generate map
		if arr[0] == "msz":
			g_x = int(arr[1])
			g_z = int(arr[2])
			var camera_script = preload("res://Script/Camera_lvl.gd")
			get_node("Camera").h_offset = g_x / 2.0
			get_node("Camera").v_offset = g_z / 2.0
			get_node("Camera").fov = g_x * 2.0
			create_map()
		# new player
		elif arr[0] == 'pnw':
			# pnw #n X Y O L N
			print('new player: ' + arr[6])
			if arr[6] != 'GRAPHIC' and arr[6] != '(null)':
				add_trantorien(arr[1], Vector3(int(arr[2]), 0.5, int(arr[3])), int(arr[4]), int(arr[5]), arr[6])
				$CanvasLayer/Panel/VBoxContainer/players.bbcode_text += '\n' + "\n[color=" + color[cnt_color % 7] + "]" + arr[1] + "[/color]"
		# move player
		elif arr[0] == 'ppo':
			#"ppo #n X Y O\n"
			move_trantorien(arr[1], Vector3(int(arr[2]), 0.5, int(arr[3])), int(arr[4]))
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
			list_team[arr[1]] = child1
			cnt_color += 1
		elif arr[0] == 'pex':
#			"pex #n\n"
			var obj_player = list_player[arr[1]]
			obj_player.kick()
		# un joueur fait un broadcast
		elif arr[0] == 'pbc':
			pass
		# lance incantation
		elif arr[0] == 'pic':
#			"pic X Y L #n #n …\n"
			var len_arr = len(arr)
			var i = 3
			while i < len_arr:
				var obj = list_player[arr[i]]
				obj.start_incantation()
				i += 1
		# fin de l’incantation sur la case donnée avec le résultat R
		elif arr[0] == 'pie':
			var len_arr = len(arr)
			var i = 3
			while i < len_arr:
				var obj = list_player[arr[i]]
				obj.start_incantation()
				i += 1
		elif arr[0] == 'plv':
			var obj = list_player[arr[1]]
			var scale = obj.scale + 0.1
			obj.scale = scale
		# le joueur est mort de faim.
		elif arr[0] == 'pdi':
			die_trantorien(arr[1])
		# le joueur jette une ressource
		elif arr[0] == 'pdr':
			if arr[1] in list_player:
				var player = list_player[arr[1]]
				var vec_player = player.translation #[TRANTORIEN.VEC]
				#var obj_player = player[TRANTORIEN.OBJ]
				var color_gem = int(arr[2])
				player.putdown(color_gem)
				if color_gem in map[vec_player.x][vec_player.z].gems:
					var obj = map[vec_player.x][vec_player.z].gems[color_gem]
					obj[0] += 1
					var scale = calc_scale(float(obj[0]))
					obj[1].scale = scale;
				else:
					insert_result_map(vec_player, 1, color_gem)
		# le joueur prend une ressource
		elif arr[0] == 'pgt':
			if arr[1] in list_player:
				var player = list_player[arr[1]]
				var vec_player = player.translation #[TRANTORIEN.VEC]
				#var obj_player = player[TRANTORIEN.OBJ]
				var color_gem = int(arr[2])
				player.putdown(color_gem)
				if color_gem in map[vec_player.x][vec_player.z].gems:
					var obj = map[vec_player.x][vec_player.z].gems[color_gem]
					obj[0] -= 1
					var scale = calc_scale(float(obj[0]))
					obj[1].scale = scale;
		# Le joueur pond un œuf.
		elif arr[0] == 'pfk':
			# animation
			pass
		# loeuf a ete pondu
		elif arr[0] == 'enw':
			# enw #e #n X Y
			# fin animation
			if arr[2] in list_player:
				var vec_player =  Vector3(int(arr[3]), 0.5, int(arr[4])) #list_player[arr[2]][TRANTORIEN.VEC]
				var obj = add_block(egg, vec_player);
				list_egg[arr[1]] = [obj, vec_player, arr[2]]
		# loeuf eclot
		elif arr[0] == 'eht':
			# animation eclosion
			die_egg(arr[1])
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
		
#		else:
#			print("Commande not set: '%s'" % line)

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
