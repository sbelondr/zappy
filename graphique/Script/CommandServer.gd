extends Node

class_name CommandServer

# time unit
var TIME: float = 1

#onready var Levels = preload("res://Script/Level.gd")
#onready var Levels = preload("res://Level.tscn")
var level

func _init(plevel):
	print("ici")
	level = plevel #Levels.instance() #new()

func inc_dec_time(is_inc: bool):
	if is_inc:
		if TIME > 0.21:
			TIME -= 0.2
	else:
		TIME += 0.2

func command_server(arr, client):
	# generate map
	if arr[0] == "msz":
		level.set_map_and_camera(int(arr[1]), int(arr[2]))
	# new player
	elif arr[0] == 'pnw':
		# pnw #n X Y O L N
		if arr[6] != 'GRAPHIC' and arr[6] != '(null)':
			var position: Vector3 = Vector3(int(arr[2]), 0.5, int(arr[3]))
			add_new_player(arr[1], position, arr[4], int(arr[5]), arr[6], \
					TIME)
	# move player
	elif arr[0] == 'ppo':
		#"ppo #n X Y O\n"
		var position = Vector3(int(arr[2]), 0.5, int(arr[3]))
		level.move_trantorien(arr[1], position, arr[4], TIME)
	# set time
	elif arr[0] == 'sgt':
		TIME = 1.0 / int(arr[1])
	# add gem
	elif arr[0] == 'bct':
		level.add_all_gem(arr)
	# add team in HUD
	elif arr[0] == 'tna':
		level.add_team_hud(arr[1])
	elif arr[0] == 'pex':
		# "pex #n\n"
		level.player_kicked(arr[1])
	# un joueur fait un broadcast
	elif arr[0] == 'pbc':
		var msg = ''
		for i in range(2, len(arr)):
			msg += " " + arr[i]
		level.player_broadcast(arr[1], msg)
#		$HUD/logs.text = arr[1] + ': ' + msg + '\n'
	# lance incantation
	elif arr[0] == 'pic':
#		"pic X Y L #n #n …\n"
		var len_arr = len(arr)
		var i = 4
		var arr_player: Array = []
		while i < len_arr:
			arr_player.push(arr[1])
			i += 1
		level.player_incantation(arr_player)
	# fin de l’incantation sur la case donnée avec le résultat R
	elif arr[0] == 'pie':
		pass
	elif arr[0] == 'plv':
		level.player_level(arr[1], int(arr[2]))
	# inventaire joueur
	elif arr[0] == 'pin':
#		pin #n X Y q q q q q q q
		level.player_set_inventory(arr[1], [arr[4], arr[5], arr[6], arr[7], \
				arr[8], arr[9], arr[10]])
	# le joueur est mort de faim.
	elif arr[0] == 'pdi':
		level.player_die(arr[1])
	# le joueur jette une ressource
	elif arr[0] == 'pdr':
		# pdr #n i
		var color_gem = int(arr[2])
		level.player_putdown_item(arr[1], color_gem)
	elif arr[0] == 'pgt':
		var color_gem = int(arr[2])
		level.player_pickup_item(arr[1], color_gem)
	# Le joueur pond un œuf.
	elif arr[0] == 'pfk':
		level.player_fork_start(arr[1])
		# animation
	# loeuf a ete pondu
	elif arr[0] == 'enw':
		# enw #e #n X Y
		# fin animation
		var position =  Vector3(int(arr[3]), 0.5, int(arr[4]))
		level.spawn_egg(arr[1], arr[2], position)
	# loeuf eclot
	elif arr[0] == 'eht':
		# animation eclosion
		level.die_egg(arr[1])
	# joueur connecte pour l'oeuf
	elif arr[0] == 'ebo':
		pass
	# l'oeuf est mort
	elif arr[0] == 'edi':
		level.die_egg(arr[1])
	# fin du jeu
	elif arr[0] == 'seg':
		level.game_over(arr[1])
	# message serveur
	elif arr[0] == 'smg':
		level.message_server(arr[1])
	else:
		if len(arr) > 1:
			print(arr)
