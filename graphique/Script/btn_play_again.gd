extends Button

func _on_btn_play_again_pressed():
# warning-ignore:return_value_discarded
	get_tree().change_scene("res://Scene/Level.tscn")
