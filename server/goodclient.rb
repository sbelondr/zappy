# frozen_string_literal: true

require 'socket'

if ARGV.empty?
puts "You must pass the team name as first argument"
end

def main
	array = ['voir', 'avance', 'droite', 'gauche', 'prendre FOOD', 'poser FOOD', 'fork']
	s = TCPSocket.new 'localhost', 8080
	puts s.recv(99)
	s.puts ARGV[0] 
	puts "SENT TEAM"
	data = s.recv(99).split('\n')
	puts data
	s.puts 'voir'
	loop do
		s.puts array.sample
		s.recv(99)
	end
end
main
