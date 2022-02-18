#extends Node
#
#
#func command_server(arr):
#	# generate map
#	if arr[0] == "msz":
#		g_x = int(arr[1])
#		g_z = int(arr[2])
#		var camera_script = preload("res://Script/Camera_lvl.gd")
#		get_node("Camera").h_offset = g_x / 2.0
#		get_node("Camera").v_offset = g_z / 2.0
#		get_node("Camera").fov = g_x * 2.0
#		create_map()
#	# new player
#	elif arr[0] == 'pnw':
#		# pnw #n X Y O L N
#		print('new player: ' + arr[6])
#		if arr[6] != 'GRAPHIC' and arr[6] != '(null)':
#			add_trantorien(arr[1], Vector3(int(arr[2]), 0.5, int(arr[3])), int(arr[4]), int(arr[5]), arr[6])
#			$CanvasLayer/Panel/VBoxContainer/players.bbcode_text += '\n' + "\n[color=" + color[cnt_color % 7] + "]" + arr[1] + "[/color]"
#	# move player
#	elif arr[0] == 'ppo':
#		#"ppo #n X Y O\n"
#		move_trantorien(arr[1], Vector3(int(arr[2]), 0.5, int(arr[3])), int(arr[4]))
#	# set time
#	elif arr[0] == 'sgt':
#		TIME = 1.0 / int(arr[1])
#	# add gem
#	elif arr[0] == 'bct':
#		add_all_gem(arr)
#	# add team in HUD
#	elif arr[0] == 'tna':
#		$CanvasLayer/Panel/VBoxContainer/teams.bbcode_text += "\n[color=" + color[cnt_color % 7] + "]" + arr[1] + "[/color]"
#		var child1 = tree.create_item(root_tree)
#		child1.set_text(0, arr[1])
#		list_team[arr[1]] = child1
#		cnt_color += 1
#	elif arr[0] == 'pex':
##		"pex #n\n"
#		var obj_player = list_player[arr[1]]
#		obj_player.kick()
#	# un joueur fait un broadcast
#	elif arr[0] == 'pbc':
#		pass
#	# lance incantation
#	elif arr[0] == 'pic':
##		"pic X Y L #n #n …\n"
#		var len_arr = len(arr)
#		var i = 3
#		while i < len_arr:
#			var obj = list_player[arr[i]]
#			obj.start_incantation()
#			i += 1
#	# fin de l’incantation sur la case donnée avec le résultat R
#	elif arr[0] == 'pie':
#		var len_arr = len(arr)
#		var i = 3
#		while i < len_arr:
#			var obj = list_player[arr[i]]
#			obj.start_incantation()
#			i += 1
#	elif arr[0] == 'plv':
#		var obj = list_player[arr[1]]
#		var scale = obj.scale + 0.1
#		obj.scale = scale
#		# le joueur est mort de faim.
#	elif arr[0] == 'pdi':
#			die_trantorien(arr[1])
#		# le joueur jette une ressource
#	elif arr[0] == 'pdr':
#		if arr[1] in list_player:
#			var player = list_player[arr[1]]
#			var vec_player = player.translation
#			var color_gem = int(arr[2])
#			player.putdown(color_gem)
#			map[vec_player.x][vec_player.z].add_item(color_gem)
#	elif arr[0] == 'pgt':
#		if arr[1] in list_player:
#			var player = list_player[arr[1]]
#			var vec_player = player.translation
#			var color_gem = int(arr[2])
#			player.putdown(color_gem)
#			map[vec_player.x][vec_player.z].remove_item(color_gem)
#	# Le joueur pond un œuf.
#	elif arr[0] == 'pfk':
#		list_player[arr[1]].fork_start()
#		# animation
#		pass
#	# loeuf a ete pondu
#	elif arr[0] == 'enw':
#		# enw #e #n X Y
#		list_player[arr[2]].fork_end()
#		# fin animation
#		if arr[2] in list_player:
#			var vec_player =  Vector3(int(arr[3]), 0.5, int(arr[4]))
#			var obj = add_block(egg, vec_player);
#			list_egg[arr[1]] = [obj, vec_player, arr[2]]
#	# loeuf eclot
#	elif arr[0] == 'eht':
#		# animation eclosion
#		die_egg(arr[1])
#	# joueur connecte pour l'oeuf
#	elif arr[0] == 'ebo':
#		pass
#	# l'oeuf est mort
#	elif arr[0] == 'edi':
#		die_egg(arr[1])
#	# fin du jeu
#	elif arr[0] == 'seg':
#		$End/GameOver.get_node("team_win").text(arr[1] + " win !")
#		$End/GameOver.visible = true
#	# message serveur
#	elif arr[0] == 'smg':
#		pass
