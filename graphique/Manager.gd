extends Node

# Declare member variables here. Examples:
# var a = 2
# var b = "text"
var hide_hud := true setget set_hide_hud, get_hide_hud
var line_edit_cheat_enabled := true setget set_line_edit_cheat_enabled, get_line_edit_cheat_enabled

func set_hide_hud(val: bool) -> void:
	hide_hud = val

func get_hide_hud() -> bool:
	return hide_hud

func set_line_edit_cheat_enabled(val: bool) -> void:
	line_edit_cheat_enabled = val

func get_line_edit_cheat_enabled() -> bool:
	return line_edit_cheat_enabled

# Called when the node enters the scene tree for the first time.
func _ready():
	hide_hud = true
	line_edit_cheat_enabled = false

# Called every frame. 'delta' is the elapsed time since the previous frame.
#func _process(delta):
#	pass
