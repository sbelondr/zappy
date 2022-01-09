# frozen_string_literal: true

require 'socket'

if ARGV.empty?
<<<<<<< HEAD
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
=======
  puts 'You must pass the team name as first argument'
  exit
end

def path_to_food(see_string)
  array = see_string.split(",")
  index = array.index {|c| c.contains "FOOD"}
  if index == 0
    return ""
  end
  truc = 0
  lasttruc = 0
  raisonmult = 0
  while index > truc
    lasttruc = truc
    truc += 1 + 2 * raisonmult
  end
end
array = ['voir', 'avance', 'droite', 'gauche', 'prendre FOOD', 'poser FOOD', 'fork']
s = TCPSocket.new 'localhost', 8080

inventory = [10, 0, 0, 0, 0, 0, 0, 0]
puts s.recv(99)
s.puts ARGV[0]
answer = s.recv(99)
answer.split("\n")
puts "Can connect: #{answer[0]}"
puts "World dimension: #{answer[1]}"
s.puts 'voir'
loop do
  s.puts array.sample
  puts s.recv(99)
>>>>>>> 1dbd3983abd5ad0d6b9495ed046dee75d82d1cd1
end
main
