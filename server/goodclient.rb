# frozen_string_literal: true

require 'socket'

if ARGV.empty?
	puts "You must pass the team name as first argument"
end

s = TCPSocket.new 'localhost', 8080

puts s.recv(99)
s.puts ARGV[0] 
puts s.recv(99)
s.puts 'voir'
loop do
  s.puts 'avance'
  puts s.recv(99)
  s.puts 'voir'
  puts s.recv(99)
end
