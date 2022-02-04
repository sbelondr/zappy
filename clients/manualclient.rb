# frozen_string_literal: true

require 'socket'

s = TCPSocket.new 'localhost', 8080

print s.recv(99)
lign = ''
loop do
  s.puts gets.chomp
  sleep 1
  print lign.chomp while (lign = s.read_nonblock(99, nil, exception: false)) != :wait_readable
end
