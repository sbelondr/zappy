# frozen_string_literal: true

require 'socket'

s = TCPSocket.new 'localhost', 8080

puts s.recv(99)
s.puts 'goodclient'
puts s.recv(99)
s.puts 'voir'
loop do
  s.puts 'avance'
  puts s.recv(99)
  s.puts 'voir'
  puts s.recv(99)
end
