extends CanvasLayer

# Declare member variables here. Examples:
# var a = 2
# var b = "text"
signal player_selected(player)
signal player_deselected(player)

signal mode_doom()

var selected : TreeItem = null
# Called when the node enters the scene tree for the first time.
func _ready():
	$LineEdit.visible = false
	pass # Replace with function body.

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(_delta):
	if $LineEdit.visible != Manager.line_edit_cheat_enabled:
		$LineEdit.visible = Manager.line_edit_cheat_enabled
		if $LineEdit.visible:
			$LineEdit.grab_focus()
	if $Panel.visible != Manager.hide_hud:
		$Panel.visible = Manager.hide_hud
		$Tree.visible = Manager.hide_hud

func _on_Tree_item_selected():
	var select_text = $Tree.get_selected().get_text(0)
	if selected == $Tree.get_selected():
		emit_signal("player_deselected", select_text)
		selected = null
		$Tree.get_selected().deselect(0)
	else:
		emit_signal("player_selected", select_text)
		selected = $Tree.get_selected()

func _on_LineEdit_text_entered(new_text):
	print(new_text)
	if new_text == 'Doom':
		emit_signal("mode_doom")
	Manager.line_edit_cheat_enabled = false
