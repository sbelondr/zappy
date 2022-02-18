# TODO:
## Performance
- Disconnecting clients is relatively slow. 
- Vision command is heavily optimizable
- Do not start before using a profiler first
- We'll do it when everything else is working

## Client Library
- Handle level up
- Handle initial incantation server message in `listen`
- Handle kicking

## Server
- Telling clients they are dead *before* kicking them. 
- Use \~conditional compilation\~ to avoid relying on gettimeofday unless it is necessary.

## Graphics
- When using the graphics, both server and clients slows down massively.

# Client library
## Functions:

### To override:
- `take_decision`: Override this to create your client behaviour. Called constantly, does not need to be an infinite loop,
- `starter`: Override this to create your client behaviour. Called once before `take_decision` at the start of the game, then never again.
- `on_broadcast_received(msg, direction)`: Override this. Called when receiving a broadcast
- `initialize(*args)`: You *can* override this. Call `super` if you do to call parent constructor.

### Action helper:
- `pickup(item)`: Attempts to pickup `item` at the current position without verification, and updates inventory on success. Returns true/false depending on result.
- `pose(item)`:  Attempts to pose `item` at the current position without verification, and updates inventory on success. Returns true/false depending on result.
- `do_action(action)`: Send `action` to server, and blocks while listening. Returns server answer.
- `listen(only_one = false)`: Blocks while listening to server and returns answer. Only return upon receiving something other than a broadcast, unless `only_one` is `true`.
- `find_item(item)`: Returns a vector giving the 2D direction towards `item` if found, `nil` otherwise.
- `move_towards(coordinates)`: Move towards coordinates. Parameter is relative. Does not guarantee final orientation.
- `gather_item(item)`: Attempt to look up for and pickup an item. Returns true if successfull, false if failed to pickup or find.

### Misc helper:
- `item_name_to_id(item_name)`: Returns the server ID corresponding to a given item name string.
- `translate_broadcast_to_vector(direction)`: Returns a vector giving the 2D direction towards to given broadcast
- `translate_vision_to_map(index)`: Returns a vector giving the 2D direction towards a given case from the vision string.
- `available_slots`: Returns available slots on the server for the team.
- `quantity_of(item, vision_string)`: Returns amount of item on the case the client is.
- `dead?`: Returns death status.

### Class var:
- `@team_name`: The team name as given in parameter
- `@self_id`: a randomly generated ID, going from 0 to 100,000. Not guaranteed to be unique, but close enough.
- `@dead`: True if there is reason to believe the client is dead. (Such as server saying it so, for example)
- `@inventory`: Array containing stones. Server order. 
- `@food`: Hunger/food. Decreased automatically when calling `do_action`.
- `@level`: Player level.
- `@socket`: Server socket. Be careful with it.
