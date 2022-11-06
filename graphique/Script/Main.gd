extends Spatial

# global variable for the socket
const HOST: String = "localhost"
const PORT: int = 8080
const RECONNECT_TIMEOUT: float = 3.0
const Client = preload("res://Script/Client.gd")

signal server_disconnect()

var disconnect_level: bool = false

onready var CommandServer = load("res://Script/CommandServer.gd")

var command_server

var _client: Client = Client.new()
onready var level = get_node("World/Level")

func _ready():
	command_server = CommandServer.new(level)
	# manage connection socket
	add_child(_client)
# warning-ignore:return_value_discarded
	_client.connect("connected", self, "_handle_client_connected")
# warning-ignore:return_value_discarded
	_client.connect("disconnected", self, "_handle_client_disconnected")
# warning-ignore:return_value_discarded
	_client.connect("data", self, "_handle_client_data")
# warning-ignore:return_value_discarded
	_client.connect("error", self, "_handle_client_error")
	_client.connect_to_server(HOST, PORT)

func _process(_delta):
	if Input.is_action_just_pressed("+"):
		command_server.inc_dec_time(false)
	if Input.is_action_just_pressed("-"):
		command_server.inc_dec_time(true)
	if Input.is_action_just_pressed("quit"):
		get_tree().quit()
	if Input.is_action_just_pressed("reload"):
# warning-ignore:return_value_discarded
		get_tree().reload_current_scene()

# Manage connection server

func _handle_client_connected() -> void:
	print("Client connected to server.")
	_client.send_var("GRAPHIC")

func _handle_client_data(data: PoolByteArray) -> void:
	var msg := data.get_string_from_utf8().split('\n')
	for line in msg:
		var arr : Array = line.split(' ')
		command_server.command_server(arr, _client)

onready var timer: Timer = get_node("World/CanvasMain/Timer")
onready var labelTimer: Label = get_node("World/CanvasMain/labTimer")
onready var logs: RichTextLabel = get_node("World/CanvasMain/logs")

func _connect_after_timeout(timeout: float) -> void:
	logs.add_text("Dans timeout.\n")
	emit_signal("server_disconnect")
	timer.start(timeout)
#	level.queue_free()
#	level = "res://Scene/Level.tscn".instance()
#	get_tree().reload_current_scene()
#	timer.connect("timeout", labelTimer, "toggle_visibility")
#	yield(get_tree().create_timer(timeout), "timeout")

func _handle_client_disconnected() -> void:
	print("Client disconnected from server.")
	logs.add_text("Client disconnected from server.\n")
	_connect_after_timeout(RECONNECT_TIMEOUT)

func _handle_client_error() -> void:
	print("Client error.")
	logs.add_text("Client error.\n")
	_connect_after_timeout(RECONNECT_TIMEOUT)

func _on_Timer_timeout():
	logs.add_text("Fin timeout\n")
	timer.stop()
	_client.connect_to_server(HOST, PORT)
