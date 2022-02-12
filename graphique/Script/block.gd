extends Spatial

var item_names := ["Food", "Linemate", "Deraumere", "Sibur", "Mendiane", "Phiras", "Thystame"]
var block_content := [0, 0, 0, 0, 0, 0, 0]

# calc scale for the items
func calc_scale(quantity: int):
	var scale := 1.0
	if quantity > 9:
		quantity = 9
	if quantity < 0:
		quantity = 0
	scale = quantity / 100.0
	scale *= 2
	return Vector3(scale, scale, scale)
	

#Add *one* item
#item_id is based off the server's list
func add_item(item_id: int):
	var item : Spatial = get_node("Materials/%s" % item_names[item_id])
	block_content[item_id] += 1
	item.visible = block_content[item_id] != 0
	item.scale = calc_scale(block_content[item_id])

#Remove *one* item
#item_id is based off the server's list
func remove_item(item_id: int):
	var item : Spatial = get_node("Materials/%s" % item_names[item_id])
	block_content[item_id] -= 1
	item.visible = block_content[item_id] != 0
	item.scale = calc_scale(block_content[item_id])

#Change the whole inventory, useful during setup / desync
#The inventory is represented with an array of size 7
func set_inventory(inventory: Array):
	block_content = inventory
	for item_id in len(block_content):
		get_node("Materials/%s" % item_names[item_id]).visible = block_content[item_id] != 0
		get_node("Materials/%s" % item_names[item_id]).scale = calc_scale(block_content[item_id])
	
	
func _ready():
	for child in get_node("Materials").get_children():
		child.visible = false
