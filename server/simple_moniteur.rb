# frozen_string_literal: true

require 'socket'

s = TCPSocket.new 'localhost', 8080

puts s.recv(99)
s.puts 'GRAPHIC'
lign = ''
loop do
  print lign while (lign = s.read_nonblock(99, nil, exception: false)) != :wait_readable
end
