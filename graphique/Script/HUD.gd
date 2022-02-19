extends CanvasLayer


# Declare member variables here. Examples:
# var a = 2
# var b = "text"
signal player_selected(player)
signal player_deselected(player)

# Called when the node enters the scene tree for the first time.
func _ready():
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
#func _process(delta):
#	pass


func _on_Tree_item_selected():
	print('ok')
	var select_text = $Tree.get_selected().get_text(0)
	emit_signal("player_selected", select_text)
	pass # Replace with function body.


func _on_Tree_item_activated():
	print('ko')
	
	emit_signal("player_deselected", $Tree.get_selected().get_text(0))
	pass # Replace with function body.
