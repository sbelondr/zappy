extends Node

# signal
signal data
signal error
signal disconnected
signal connected

# global
var client
var wrapped_client
var _status: int = 0

func _ready():
	client = StreamPeerTCP.new()
	client.set_no_delay(true)

func state_connection(new_status):
	if new_status != _status:
		_status = new_status
		match _status:
			client.STATUS_NONE:
				emit_signal("disconnected")
			client.STATUS_CONNECTING:
				print("Connecting to host.")
			client.STATUS_CONNECTED:
				emit_signal("connected")
			client.STATUS_ERROR:
				emit_signal("error")

func srv_send_msg():
	var available_bytes: int = client.get_available_bytes()
	if available_bytes > 0:
#		print("available bytes: ", available_bytes)
		var data: Array = client.get_partial_data(available_bytes)
		# Check for read error.
		if data[0] != OK:
			print("Error getting data from stream: ", data[0])
			emit_signal("error")
		else:
			emit_signal("data", data[1])

func _process(delta):
	var new_status: int = client.get_status()
	state_connection(new_status)
	if new_status == client.STATUS_CONNECTED:
		srv_send_msg()

func connect_to_server(ip, port):
	set_process(true)
	print("Connecting to server: %s : %s" % [ip, str(port)])
	var connect = client.connect_to_host(ip, port)
	if client.is_connected_to_host():
		wrapped_client = PacketPeerStream.new()
		wrapped_client.set_stream_peer(client)

func disconnect_from_server():
	client.disconnect_from_host()
	emit_signal("disconnected")
	
func get_data(data):
	print("Client data: ", data.get_string_from_utf8())

func send_var(msg):
	if client.is_connected_to_host():
		print("Sending: %s" % msg)
		msg = msg + "\n"
		wrapped_client.get_stream_peer().put_data(msg.to_ascii())
		var error = wrapped_client.get_packet_error()
		if error != 0:
			print("Error on packet put: %s" % error)