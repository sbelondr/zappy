# frozen_string_literal: true

require 'socket'

s = TCPSocket.new 'localhost', 8080

puts s.recv(99)
s.puts 'GRAPHIC'
loop do
  puts s.recv(999)
end
