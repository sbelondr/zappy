extends Spatial

var level := 1
var inventory := [0, 0, 0, 0, 0, 0, 0, 0]

onready var animPlayer : AnimationPlayer = get_node("AnimationPlayer")
onready var tween : Tween = get_node("Tween")

func _ready():
	animPlayer.get_animation("WalkCycle").set_loop(true)
	animPlayer.get_animation("Ritual1").set_loop(true)
	animPlayer.get_animation("Ritual2").set_loop(true)
	animPlayer.get_animation("Ritual3").set_loop(true)
	animPlayer.get_animation("Ritual4").set_loop(true)
	animPlayer.get_animation("Pose").set_loop(true)
	
#Move trantorien to target direction, speed is TIME
#Handles animation and tweening, PLEASE CALL THIS
func move_trantorien(dest: Vector3, speed: float) -> void:
	tween.interpolate_property(self, "translation", null, dest, speed, Tween.TRANS_CUBIC)
	tween.start()
	animPlayer.play("WalkCycle")

#Take an item from the ground (no check done)
#Handle animation and all, PLEASE CALL THIS
func pickup(item_id: int) -> void:
	animPlayer.play("Pickup")
	inventory[item_id] += 1

#Put an item on the ground (no check done)
#Handle animation and all, PLEASE CALL THIS
func putdown(item_id: int) -> void:
	animPlayer.play_backwards("Pickup")
	inventory[item_id] -= 1

#Start ritual animation
#Play a different animation for each level, PLEASE CALL THIS
func start_incantation() -> void:
	var ritual_level := level
	if level > 4:
		ritual_level = 4
	animPlayer.play("Ritual%d" % ritual_level)

#Play the kick animation
#JUST CALL THIS PLEASE
func kick() -> void:
	animPlayer.play("Kick")
	
#Is being kicked
#Stop current animation (will play one later) and handle movement, PLEASE CALL THIS
func kicked(new_position: Vector3, speed: float) -> void:
	tween.interpolate_property(self, "translation", null, new_position, speed, Tween.TRANS_CUBIC)
	tween.start()
	animPlayer.stop()

#Play the death animation
#Handle deleting the character AFTER the animation finished, PLEASE CALL THIS
func dead() -> void:
	animPlayer.play("Death")
	animPlayer.connect("animation_finished", self, "_death_animation_finished")

#Play the idle animation when nothing else is going on
#Necessary to avoid doing stupid thing, also its a placeholder. PLEASE CALL THIS
func idle() -> void:
	animPlayer.play("Pose")

#Private function, PLEASE DO *NOT* CALL THIS
func _death_animation_finished(_animation_name: String) -> void:
	queue_free()
	
#Much better than using attributes as globals, PLEASE CALL THIS
func set_level(new_level: int) -> void:
	level = new_level
	
#Much better than using attributes as globals, PLEASE CALL THIS
func set_inventory(new_inventory: Array) -> void:
	inventory = new_inventory
