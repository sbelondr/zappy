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

# list lastname and firstname to generate Trantorien
var lastname := [
	"Dickerson",
	"Madden",
	"Ball",
	"Hahn",
	"Cole",
	"Wagner",
	"Ross",
	"Peters",
	"Molina",
	"Maynard",
	"Chase",
	"Randolph",
	"Henderson",
	"Meza",
	"Nicholson",
	"Morton",
	"Stevens",
	"Mcneil",
	"Duncan",
	"Barnes",
	"Guerrero",
	"Barton",
	"Deleon",
	"Robinson",
	"Hamilton",
	"Fitzgerald",
	"Eaton",
	"Dickson",
	"Newman",
	"Macdonald",
	"Silva",
	"Hawkins",
	"Gould",
	"Adkins",
	"Elliott",
	"Ayache",
	"Belondrade",
	"Leonard",
	"Miller",
	"Taylor",
	"Key",
	"Wyatt",
	"Benjamin",
	"Wright",
	"Lewis",
	"Sanchez",
	"Waters",
	"Lang",
	"Stephens",
	"Meyer",
	"Stanton",
	"Salas"
]

var firstname := [
	"Kristopher",
	"Brice",
	"Carlton",
	"Rusty",
	"Samuel",
	"Jordan",
	"Janice",
	"Jeannine",
	"Patti",
	"Agnes",
	"Hershel",
	"Corina",
	"Alvin",
	"Bettye",
	"Carrie",
	"Cyrus",
	"Cornell",
	"Zack",
	"Sanford",
	"Jasper",
	"Elmo",
	"Stacey",
	"Effie",
	"Thanh",
	"Greg",
	"Fredric",
	"Carey",
	"Truman",
	"Lanny",
	"Gaylord",
	"Clifton",
	"German",
	"Abel",
	"Robbie",
	"Minh",
	"Lottie",
	"Sue",
	"Lorna",
	"Odessa",
	"Reyna",
	"Mauricio",
	"Vicki",
	"Norris",
	"Israel",
	"Jacques",
	"Marion",
	"Toney",
	"Marisa",
	"Boyce",
	"Marcelino",
	"Lina",
	"Kevin"
]

# Generate new name
func generate_names() -> String:
	var fname = firstname[randi()%51]
	var lname = lastname[randi()%51]
	return fname + " " + lname

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
		player.manage_orientation_trantorien(orientation, TIME)
		if is_interpolate(player.translation.x, vec.x) \
			and is_interpolate(player.translation.y, vec.y) \
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
	pass
	
func command_server(arr):
	# generate map
	if arr[0] == "msz":
		g_x = int(arr[1])
		g_z = int(arr[2])
#		var camera_script = preload("res://Script/Camera_lvl.gd")
		get_node("Camera").h_offset = g_x / 2.0
		get_node("Camera").v_offset = g_z / 2.0
		get_node("Camera").fov = g_x * 2.0
		create_map()
	# new player
	elif arr[0] == 'pnw':
		# pnw #n X Y O L N
		if arr[6] != 'GRAPHIC' and arr[6] != '(null)':
			add_trantorien(arr[1], Vector3(int(arr[2]), 0.5, int(arr[3])), int(arr[4]), int(arr[5]), arr[6])
			$HUD/Panel/VBoxContainer/players.bbcode_text += '\n' + "\n[color=" + color[cnt_color % 7] + "]" + arr[1] + "[/color]"
			_client.send_var("pin " + arr[1])
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
		$HUD/Panel/VBoxContainer/teams.bbcode_text += "\n[color=" + color[cnt_color % 7] + "]" + arr[1] + "[/color]"
		var child1 = tree.create_item(root_tree)
		child1.set_text(0, arr[1])
		list_team[arr[1]] = child1
		cnt_color += 1
	elif arr[0] == 'pex':
#		"pex #n\n"
		$Level.player_kicked()
		var obj_player = list_player[arr[1]]
		obj_player.kick()
	# un joueur fait un broadcast
	elif arr[0] == 'pbc':
		var msg = ''
		for i in range(2, len(arr)):
			msg += " " + arr[i]
#		$HUD/logs.text = arr[1] + ': ' + msg + '\n'
		if arr[1] in list_player:
			list_player[arr[1]].broadcast(msg)
	# lance incantation
	elif arr[0] == 'pic':
#		"pic X Y L #n #n …\n"
		var len_arr = len(arr)
		var i = 4
		while i < len_arr:
			if arr[i] in list_player and list_player[arr[i]]:
				var obj = list_player[arr[i]]
				obj.start_incantation()
			i += 1
	# fin de l’incantation sur la case donnée avec le résultat R
	elif arr[0] == 'pie':
		pass
	elif arr[0] == 'plv':
		var player = list_player[arr[1]]
		player.idle()
		var level: int = int(arr[2])
		if player.level != level:
			var scale = player.scale + 0.1
			player.scale = scale
			player.set_level(level)
	# inventaire joueur
	elif arr[0] == 'pin':
#		pin #n X Y q q q q q q q
		if arr[1] in list_player:
			list_player[arr[1]].set_inventory([arr[4],arr[5],arr[6],arr[7],arr[8],arr[9],arr[10]])
	# le joueur est mort de faim.
	elif arr[0] == 'pdi':
		die_trantorien(arr[1])
	# le joueur jette une ressource
	elif arr[0] == 'pdr':
		if arr[1] in list_player:
			var player = list_player[arr[1]]
			var vec_player = player.translation
			var color_gem = int(arr[2])
			player.putdown(color_gem)
			map[vec_player.x][vec_player.z].add_item(color_gem)
	elif arr[0] == 'pgt':
		if arr[1] in list_player:
			var player = list_player[arr[1]]
			var vec_player = player.translation
			var color_gem = int(arr[2])
			player.pickup(color_gem)
			map[vec_player.x][vec_player.z].remove_item(color_gem)
	# Le joueur pond un œuf.
	elif arr[0] == 'pfk':
		if arr[1] in list_player:
			list_player[arr[1]].fork_start()
		# animation
		pass
	# loeuf a ete pondu
	elif arr[0] == 'enw':
		# enw #e #n X Y
		# fin animation
		if arr[2] in list_player:
			list_player[arr[2]].fork_end()
			var vec_player =  Vector3(int(arr[3]), 0.5, int(arr[4]))
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
		$End/GameOver.get_node("team_win").text(arr[1] + " win !")
		$End/GameOver.visible = true
	# message serveur
	elif arr[0] == 'smg':
		$HUD/logs.text = "Message server: " + arr[1]
	else:
		if len(arr) > 1:
			print(arr)

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
