extends Spatial

var level := 1
var inventory := [0, 0, 0, 0, 0, 0, 0, 0]
onready var animPlayer = get_node("AnimationPlayer")

func _ready():
	animPlayer.get_animation("WalkCycle").set_loop(true)
	
#Move trantorien to target direction
#Handles animation and tweening, PLEASE CALL THIS
func move_trantorien(dest: Vector3, speed: float) -> void:
	$Tween.interpolate_property(self, "translation", null, dest, speed, Tween.TRANS_CUBIC)
	$Tween.start()
	$AnimationPlayer.play("WalkCycle")

#Take an item from the ground (no check done)
#Handle animation and allm PLEASE CALL THIS
func pickup(item_id: int) -> void:
	$AnimationPlayer.play("Pickup")
	inventory[item_id] += 1

#Put an item on the ground (no check done)
#Handle animation and allm PLEASE CALL THIS
func putdown(item_id: int) -> void:
	$AnimationPlayer.play_backwards("Pickup")
	inventory[item_id] - 1

