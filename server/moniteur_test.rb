# frozen_string_literal: true

require 'socket'

s = TCPSocket.new 'localhost', 8080
player = TCPSocket.new 'localhost', 8080

lign = ""
data = ""

puts s.recv(99)
s.puts 'GRAPHIC'

loop do
  data += lign while (lign = s.read_nonblock(99, nil, exception: false)) != :wait_readable
	
end
