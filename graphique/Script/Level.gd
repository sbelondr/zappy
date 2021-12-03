extends Spatial

const texture_block = preload("res://Texture/block.tscn")
const trantorien = preload("res://Texture/Trantorien.tscn")
const gem = preload("res://Texture/Gem.tscn")
const gem2 = preload("res://Texture/Gem2.tscn")
const gem3 = preload("res://Texture/Gem3.tscn")
const gem4 = preload("res://Texture/Gem4.tscn")
const gem5 = preload("res://Texture/Gem5.tscn")
const gem6 = preload("res://Texture/Gem6.tscn")
const gem7 = preload("res://Texture/Gem7.tscn")
var g_x = 10
var g_z = 10

var TIME = 1

# scoket global variable
const HOST: String = "localhost"
const PORT: int = 8080
const RECONNECT_TIMEOUT: float = 3.0

const Client = preload("res://Script/Client.gd")
var _client: Client = Client.new()

var list_player = Dictionary()

const list_command = [
	"msz", # taille de la carte
	"bct",
	"bct",
	"tna",
	"pnw",
	"ppo",
	"plv",
	"pin",
	"pex",
	"pbc",
	"msz",
	"bct",
	"mct",
	"tna",
	"ppo",
	"plv",
	"pin",
	"pic",
	"pie",
	"pfk",
	"pdr",
	"pgt",
	"pdi",
	"enw",
	"eht",
	"ebo",
	"edi",
	"sgt",
	"sgt",
	"sgt",
	"seg",
	"smg",
	"suc",
	"sbp",
	"sst"]

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
func add_trantorien(name: String, vec: Vector3) -> void:
	var obj = add_block(trantorien, vec)
	list_player[name] = [obj, vec]

# deplace Trantorien
# Args:
#	name: name of Trantorien
#	vec: new position of Trantorien
func move_trantorien(name: String, vec: Vector3) -> void:
	if name in list_player:
		var player = list_player.get(name)
		var obj = player[0]
		$Tween.interpolate_property(obj, "translation", obj.translation, vec, TIME, Tween.TRANS_CUBIC)
		$Tween.start()

# remove Trantorien on the map and the list
# Arg:
#	name: name of Trantorien
func die_trantorien(name: String) -> void:
	if name in list_player:
		var obj = list_player[name][0]
		obj.queue_free()
		list_player.erase(name)

func _on_Timer_timeout():
	var vec : Vector3 = list_player["coucou"][1]
	vec.x += 1
	vec.z += 1
	list_player["coucou"][1] = vec
	if vec.x < g_x:
		move_trantorien("coucou", vec)
	else:
		$Timer.stop()
		die_trantorien("coucou")
		
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

func _ready():
#	create_map()
#	add_trantorien("coucou", Vector3(0, 1, 0))
#	launch_timer()

	# manage connection socket
	add_child(_client)
	_client.connect("connected", self, "_handle_client_connected")
	_client.connect("disconnected", self, "_handle_client_disconnected")
	_client.connect("data", self, "_handle_client_data")
	_client.connect("error", self, "_handle_client_error")
	_client.connect_to_server(HOST, PORT)
#	_client.send_var("msz")

func _handle_client_connected() -> void:
	print("Client connected to server.")
	_client.send_var("GRAPHIC")

func _handle_client_data(data: PoolByteArray) -> void:
	var msg = data.get_string_from_utf8().split('\n')
	for line in msg:
		var arr = line.split(' ')
		if arr[0] == "msz":
			print('map')
			g_x = int(arr[1])
			g_z = int(arr[2])
			create_map()
		elif arr[0] == 'pnw':
			print('new player: ' + arr[6])
#		pnw #n X Y O L N\
			if arr[6] != 'GRAPHIC' and arr[6] != '(null)':
				add_trantorien(arr[1], Vector3(int(arr[2]), 1, int(arr[3])))
		elif arr[0] == 'ppo':
			print('position')
			#"ppo #n X Y O\n"
			move_trantorien(arr[1], Vector3(int(arr[2]), 1, int(arr[3])))
		elif arr[0] == 'sgt':
			TIME = int(arr[1])
		elif arr[0] == 'bct':
			# q q q q q q q
#			if (int(arr[1]) == 19 and int(arr[2]) == 19):
#				print("ok")
#				add_block(gem, Vector3(19, 1, 19))
#				add_block(gem2, Vector3(19, 1, 19))
#				add_block(gem3, Vector3(19, 1, 19))
#				add_block(gem4, Vector3(19, 1, 19))
#				add_block(gem5, Vector3(19, 1, 19))
#				add_block(gem6, Vector3(19, 1, 19))
#				add_block(gem7, Vector3(19, 1, 19))
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
		else:
			print("Commande not set: ", line)
		

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
