# frozen_string_literal: true

require 'socket'

if ARGV.empty?
  puts "You must pass the team name as first argument"
end

class Trantorien
  def initialize(socket)
    @food = 10
    @hunger = 0
    @socket = socket
  end

  def pickup(item)
    @socket.puts "prendre #{item}"
    if @socket.recv(99) == "OK\n"
      if item == "FOOD"
        @food += 1
        puts "Gained one food !! Current food: #{@food}"
      end
    end

  end
  def do_action(action)
    #Bookeep ressources...
    if ["voir", "avance", "droite", "gauche"].include? action
      reduce_hunger(7)
    end
    @socket.puts action
    @socket.recv(999)
  end

  def reduce_hunger(amount)
    if @hunger < amount
      @food -= 1
      amount -= @hunger
      @hunger = 126 - amount
    else
      @hunger -= amount
    end
  end

  def move_towards(coordinates)
    coordinates[1].times do
      do_action "avance"
    end
    if (coordinates[0] > 0)
      do_action "gauche"
    elsif (coordinates[0] < 0)
      do_action "droite"
    end
    coordinates[0].times do
      do_action "avance"
    end
  end

  def translate_vision_to_map(index)
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

  def find_food
    vision = []
    vision = do_action("voir").split(",")
    puts "#{vision}"
    vision.each do |area, index|
      if area.include? "FOOD"
        move_towards(translate_vision_to_map(index))
        pickup("FOOD")
        return true
      end
    end
    return false
  end
end

def main
  array = ['voir', 'avance', 'droite', 'gauche', 'prendre FOOD', 'poser FOOD', 'fork']
  s = TCPSocket.new 'localhost', 8080
  puts s.recv(99)
  s.puts ARGV[0] 
  puts "SENT TEAM"
  data = s.recv(99).split('\n')
  player = Trantorien.new(s)
  puts data
  loop do
    player.find_food
    player.do_action(["avance", "droite", "gauche"].sample)
  end
end
main
