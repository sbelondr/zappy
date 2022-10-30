extends CanvasLayer

# Declare member variables here. Examples:
# var a = 2
# var b = "text"
signal player_selected(player)
signal player_deselected(player)

signal mode_doom()
signal debug_me(name_team)

onready var line_edit : LineEdit = get_node("LineEdit");
onready var panel: Panel = get_node("Panel");
onready var tree: Tree = get_node("Tree");

var selected : TreeItem = null
# Called when the node enters the scene tree for the first time.
func _ready():
	line_edit.visible = false
	pass # Replace with function body.

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(_delta):
	if line_edit.visible != Manager.line_edit_cheat_enabled:
		line_edit.visible = Manager.line_edit_cheat_enabled
		if line_edit.visible:
			line_edit.grab_focus()
	if panel.visible != Manager.hide_hud:
		panel.visible = Manager.hide_hud
		tree.visible = Manager.hide_hud

func _on_Tree_item_selected():
	var select_text = tree.get_selected().get_text(0)
	if selected == tree.get_selected():
		emit_signal("player_deselected", select_text)
		selected = null
		tree.get_selected().deselect(0)
	else:
		emit_signal("player_selected", select_text)
		selected = tree.get_selected()

func _on_LineEdit_text_entered(new_text):
	print(new_text)
	var val = new_text.split(' ')
	print (val)
	if new_text == 'Doom':
		emit_signal("mode_doom")
	elif val[0] == 'd':
		emit_signal("debug_me", val[1])
	Manager.line_edit_cheat_enabled = false
