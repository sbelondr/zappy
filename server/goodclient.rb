# frozen_string_literal: true

require 'socket'

if ARGV.empty?
	puts "You must pass the team name as first argument"
end

array = ['voir', 'avance', 'droite', 'gauche', 'prendre FOOD', 'poser FOOD', 'fork']
s = TCPSocket.new 'localhost', 8080

puts s.recv(99)
s.puts ARGV[0] 
puts s.recv(99)
s.puts 'voir'
loop do
  s.puts array.sample
  puts s.recv(99)
end
