extends CanvasLayer


# Declare member variables here. Examples:
# var a = 2
# var b = "text"
signal player_selected(player)

# Called when the node enters the scene tree for the first time.
func _ready():
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
#func _process(delta):
#	pass


func _on_Tree_item_selected():
	emit_signal("player_selected", $Tree.get_selected().get_text(0))
	pass # Replace with function body.
