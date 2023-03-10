# frozen_string_literal: true

require 'socket'

if ARGV.empty?
  puts "You must pass the team name as first argument"
end

$clients = []
def start_new_client
  puts "Creating new client"
  $clients.push Thread.new {
    s = nil
    begin
      s = TCPSocket.new 'localhost', 8080
    rescue
       return 
    end
    puts "Connecting to server..."
    puts s.recv(99)
    s.puts ARGV[0] 
    puts "Sent team #{ARGV[0]}..."
    data = s.recv(99).split('\n')
    player = Trantorien.new(s)
    puts data
    loop do
      player.process
    end
  }
end

class Trantorien
  def initialize(socket)
    @food = 10
    @hunger = 0
    @socket = socket
  end

  def process
    if @food < 10
      if not find_food
        do_action(["avance", "droite"].sample)
      end
    else
      do_action("fork")
    end
    if do_action("connect_nbr").to_i > 0
      start_new_client
    end
  end

  def pickup(item)
    @socket.puts "prendre #{item}"
    if @socket.recv(99) == "OK\n"
      if item == "FOOD"
        @food += 1
        puts "Gained one food !! Current food: #{@food}"
      end
    else
      puts "Pickup failed for item #{item}!! WHAT DO I DO??!!"
    end

  end
  def do_action(action)
    #Bookeep ressources...
    if ["voir", "avance", "droite", "gauche"].include? action
      reduce_hunger(7)
    elsif action == "fork"
      reduce_hunger(42)
    end
    ret = ""
    begin
    @socket.puts action
    ret = @socket.recv(999)
    rescue 
      puts "Connection to socket got screwed"
      puts "I don't know what to do...."
      puts "Goodbye!!!"
      sleep 10
    end
    ret
  end

  def reduce_hunger(amount)
    if @hunger < amount
      @food -= 1
      amount -= @hunger
      @hunger = 126 - amount
    else
      @hunger -= amount
      puts "Getting hungrier ! Current hunger: #{@hunger}(-#{amount}) with food #{@food}!"
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
    else
    end
    coordinates[0].abs.times do
      do_action "avance"
    end
  end

  def translate_vision_to_map(index)
    puts "Found something at index #{index}"
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
    vision.each_with_index do |area, index|
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
  data = s.recv(99).split('\n')
  player = Trantorien.new(s)
  puts data
  loop do
    player.process
  end
end
main
