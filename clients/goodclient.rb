# frozen_string_literal: true

require 'socket'

if ARGV.empty?
	puts "You must pass the team name as first argument"
end

#0 -> x (sides)
#1 -> y (front)
def move_towards(socket, coordinates)
	coordinates[1].times do
		socket.puts "avance"
		socket.recv(99)
	end
	if (coordinates[0] > 0)
		socket.puts "droite"
		socket.recv(99)
	else if (coordinates[0] < 0)
		socket.puts "droite"
		socket.recv(99)
	end
	coordinates[0].times do
		socket.puts "avance"
		socket.recv(99)
	end
end

def find_food(socket)
	vision = []
	socket.puts "voir"
	vision = s.recv(199).split(",")
	vision.each do |area, index|
		if area.include? "FOOD"
			move_towards(socket, translate_1d_to_2d(index))
			socket.puts "prendre FOOD"
			sockets.recv(99)
			return
		end
	end
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
	end
end
main
