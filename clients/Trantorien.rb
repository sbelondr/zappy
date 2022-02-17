# frozen_string_literal: true

require 'socket'
require 'optparse'

module Client

  class Trantorien
    def initialize(team_name, ip = "localhost", port = 8080)
      @team_name = team_name
      @self_id = rand(100000)
      @dead = false
      @food = 126 * 10
      @inventory = [0, 0, 0, 0, 0, 0, 0]
      @socket = TCPSocket.new ip, port 
      @socket.recv(99)
      @socket.puts @team_name 
      data = @socket.recv(99).split("\n")
      if data[0].to_i == 0
        @dead = true
      end
    end

    def dead?
      @dead
    end

    def take_decision
      puts "Override me!"
    end

    def process
      starter if not @dead
      while not @dead
        take_decision
      end
    end

    def starter 
      puts "Override me!"
    end

    def update_inventory
      inventory = do_action "inventaire"
      inventory = inventory.split ","
      inventory.each do |item|
          @food = item.split[1].to_i if item.contains? "nourriture"
          @inventaire[item_name_to_id "phiras"] = item.split[1].to_i if item.contains? "phiras"
          @inventaire[item_name_to_id "sibur"] = item.split[1].to_i if item.contains? "sibur"
          @inventaire[item_name_to_id "deraumere"] = item.split[1].to_i if item.contains? "deraumere"
          @inventaire[item_name_to_id "mendiane"] = item.split[1].to_i if item.contains? "mendiane"
          @inventaire[item_name_to_id "thystame"] = item.split[1].to_i if item.contains? "thystame"
          @inventaire[item_name_to_id "linemate"] = item.split[1].to_i if item.contains? "linemate"
      end
    end

    def pickup(item)
      ret = do_action("prendre #{item}")
      if ret == "ok"
        if item == "FOOD"
          @food += 126
        else
          @inventory[item_name_to_id(item)] += 1
        end
        true
      else
        puts "Pickup failed for item #{item}!! WHAT DO I DO??!!"
        false
      end
    end

    def pose(item)
      ret = do_action("prendre #{item}")
      if ret == "ok"
        if item == "FOOD"
          @food -= 126
        else
          @inventory[item_name_to_id(item)] -= 1
        end
        true
      else
        puts "Pose failed for item #{item}!! WHAT DO I DO??!!"
        false
      end
    end

    def item_name_to_id(item_name)
      return 0 if item_name == "FOOD"
      return 1 if item_name == "LINEMATE"
      return 2 if item_name == "DERAUMERE"
      return 3 if item_name == "SIBUR"
      return 4 if item_name == "MENDIANE"
      return 5 if item_name == "PHIRAS"
      return 6 if item_name == "THYSTAME"
    end

    #Do an action, blocking till it gets an answer
    def do_action(action)
      if ["broadcast", "voir", "avance", "droite", "gauche"].include? action
        reduce_hunger(7)
      elsif action == "fork"
        reduce_hunger(42)
      end
      ret = ""
      begin
        @socket.puts action
        ret = listen
      rescue Errno::ECONNREFUSED 
        puts "#{@self_id}: Server booted me!!"
        @dead = true
      end
      ret
    end

    def listen(only_one = false)
      answered = false
      response = ""
      while not answered
        response = @socket.gets.chomp
        puts "#{@self_id}: #{response}"
        if response.start_with? "message "
          tmp = response.split ','
          on_broadcast_received(tmp[1], tmp[0].split(' ')[1].to_i)
        else
          answered = true
        end
        break if only_one
      end
      response
    end

    def on_broadcast_received(msg, direction)
      puts "I received #{msg} from #{direction} !!"
    end

    def reduce_hunger(amount)
      @food -= amount
    end

    #TODO: reduce the amount of action to go back
    def move_towards(coordinates)
      if coordinates[1] < 0
        do_action "droite"
        do_action "droite"
      end
      coordinates[1].abs.times do
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

    def translate_broadcast_to_vector(index)
      return [0, 0] if index == 0
      return [0, 1] if index == 1
      return [-1, 1] if index == 2
      return [-1, 0] if index == 3
      return [-1, -1] if index == 4
      return [0, -1] if index == 5
      return [1, -1] if index == 6
      return [1, 0] if index == 7
      return [1, 1] if index == 8
      puts "ERROR: invalid index: #{index}" 
      nil
    end

    #Returns coordinates to object if seen, nil otherwise
    def find_item(item)
      vision = []
      vision = do_action("voir").split(",")
      vision.each_with_index do |area, index|
        if area.include? item 
          return translate_vision_to_map(index)
        end
      end
      return nil 
    end

    def available_slots
      do_action("connect_nbr").to_i
    end
  end

  def self.main(trantorien)
    options = self.parse
    p options
    threads = []
    loop do
      tt = trantorien.new options[:team] 
      if not tt.dead?
        threads << Thread.new { tt.process } 
      end
      sleep options[:delay]
    end
    threads.each { |thr| thr.join }
  end

  def self.parse
    options = {:delay => 1}
    OptionParser.new do |parser|
      parser.banner = "Usage: #{File.basename($0)} -t team [-d delay]"

      parser.on("-t", "--team TEAM", String, "Player team")
      parser.on("-d", "--delay SECONDS", Integer, "Attempt connecting each SECONDS seconds. Defaults to 1")
      parser.on("-h", "--help", "Display this help") { puts parser; exit }

    end.parse!(into: options)
    if options[:team].nil?
      exit
    end
    options 
  end
end
