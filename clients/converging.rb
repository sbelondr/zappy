# frozen_string_literal: true

require 'socket'
require "./Trantorien.rb"

if ARGV.empty?
  puts "You must pass the team name as first argument"
  exit 1
end

class Converging < Trantorien
  def initialize(socket)
    super socket
  end

  def process
    if @food < 126 * 10
      if not find_food
        do_action(["avance", "droite"].sample)
      end
    else
      do_action("broadcast I AM FULL")
    end
  end

  def on_broadcast_received(msg, direction)
    puts "I received #{msg} from #{direction} !!"
  end

  def find_food
    pos = find_item("FOOD")
    if pos != nil
      move_towards(pos)
      return pickup("FOOD")
    end
    false
  end
end

def main
  array = ['voir', 'avance', 'droite', 'gauche', 'prendre FOOD', 'poser FOOD', 'fork']
  s = TCPSocket.new 'localhost', 8080
  puts s.recv(99)
  s.puts ARGV[0] 
  data = s.recv(99).split('\n')
  player = Converging.new(s)
  puts data
    Thread.new do
      s = TCPSocket.new 'localhost', 8080
      puts s.recv(99)
      s.puts ARGV[0] 
      data = s.recv(99).split('\n')
      player = Converging.new(s)
      loop do
        player.process
      end
    end
  loop do
    player.process
  end
end
main
