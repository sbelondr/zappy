# frozen_string_literal: true

require 'socket'

if ARGV.empty?
puts "You must pass the team name as first argument"
end

#0 -> x
#1 -> y
def move_towards(socket, coordinates)
	coordinates[1].times do
		socket.puts "avance"
		socket.recv(99)
	end
	if (coordinates[0] > 0)
		socket.puts "droite"
		socket.recv(99)
	elsif (coordinates[0] < 0)
		socket.puts "droite"
		socket.recv(99)
	end
	coordinates[0].times do
		socket.puts "avance"
		socket.recv(99)
	end
end

def translate_1d_to_2d(index)
	return [0, 0] if index == 0
	return [-1, 1] if index == 1
	return [0, 1] if index == 2
	return [1, 1] if index == 3
	return [-2, 2] if index == 4
	return [-1, 2] if index == 5
	return [0, 2] if index == 6
	return [1, 2] if index == 7
	return [2, 2] if index == 8
	return [5, 5]
end

def find_food(socket)
	vision = []
	socket.puts "voir"
	vision = socket.recv(199).split(",")
	puts vision
	vision.each do |area, index|
		if area.include? "FOOD"
			move_towards(socket, translate_1d_to_2d(index))
			socket.puts "prendre FOOD"
			socket.recv(99)
			return true
		end
	end
	return false
end

def main
	array = ['voir', 'avance', 'droite', 'gauche', 'prendre FOOD', 'poser FOOD', 'fork']
	s = TCPSocket.new 'localhost', 8080
	puts s.recv(99)
	s.puts ARGV[0] 
	puts "SENT TEAM"
	data = s.recv(99).split('\n')
	puts data
	loop do
		find_food(s)
		s.puts ["avance", "droite", "gauche"].sample
		s.recv(99)
	end
end
main
