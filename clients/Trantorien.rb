# frozen_string_literal: true

require 'socket'
require 'optparse'

module Client

  class Trantorien
    attr_reader :level, :dead, :food, :inventory, :self_id, :team_name

    def initialize(team_name, ip = "localhost", port = 8080)
      @team_name = team_name
      @self_id = rand(100000)
      @dead = false
      @food = 126 * 10
      @level = 1
      @inventory = [0, 0, 0, 0, 0, 0, 0]
      @socket = TCPSocket.new ip, port 
      @socket.recv(99)
      @socket.puts @team_name 
      data = @socket.gets
      if data[0].to_i == 0
        @dead = true
      end
      @socket.gets
    end

    def dead?
      @dead
    end

    def take_decision
      puts "Override me!"
    end

    def broadcast(message)
      do_action "broadcast #{broadcast_prefix}#{message}"
    end

  def broadcast_prefix
    "#{@self_id}"
  end

    def voir
      do_action "voir"
    end

    def incantation
      old_level = @level
      do_action "incantation"
      old_level != @level
    end

    def convert_vision_string vision_string
      vision = vision_string.split(',')
      vision.collect do |block|
        block.each_char.filter {|c| c != '}' && c != '{'}.join.split
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
        false
      end
    end

    def pose(item)
      ret = do_action("pose #{item}")
      if ret == "ok"
        if item == "FOOD"
          @food -= 126
        else
          @inventory[item_name_to_id(item)] -= 1
        end
        true
      else
        false
      end
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

    def inventory
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
      nil
    end


    def item_name_to_id(item_name)
      item_name = item_name.upcase
      return 0 if item_name == "FOOD"
      return 1 if item_name == "LINEMATE"
      return 2 if item_name == "DERAUMERE"
      return 3 if item_name == "SIBUR"
      return 4 if item_name == "MENDIANE"
      return 5 if item_name == "PHIRAS"
      return 6 if item_name == "THYSTAME"
    end

    def id_to_item_name(id)
      return ["FOOD", "LINEMATE", "DERAUMERE", "SIBUR", "MENDIANE", "PHIRAS", "THYSTAME"][id]
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
        Thread.exit
      end
      ret
    end

    def get_ritual_cost(level)
      [
        [0, 1, 0, 0, 0, 0, 0, 1],
        [0, 1, 1, 1, 0, 0, 0, 2],
        [0, 2, 0, 1, 0, 2, 0, 2],
        [0, 1, 1, 2, 0, 1, 0, 4],
        [0, 1, 2, 1, 3, 0, 0, 4],
        [0, 1, 2, 3, 0, 1, 0, 6], 
        [0, 2, 2, 2, 2, 2, 1, 6]
      ][level - 1]
    end

    def quantity_of(item, vision_string)
      items = vision_string.split ','
      items[0].downcase.scan(item.downcase).size
    end

    def can_do_ritual(vision, level)
      cost = get_ritual_cost level
      ret = quantity_of("FOOD", vision) >= cost[0]
      ret &&= quantity_of("LINEMATE", vision) >= cost[1]
      ret &&= quantity_of("DERAUMERE", vision) >= cost[2]
      ret &&= quantity_of("SIBUR", vision) >= cost[3]
      ret &&= quantity_of("MENDIANE", vision) >= cost[4]
      ret &&= quantity_of("PHIRAS", vision) >= cost[5]
      ret &&= quantity_of("THYSTAME", vision) >= cost[6]
      ret &&= quantity_of("PLAYER", vision) >= (cost[7] - 1)
      ret
    end

    def listen(only_one = false)
      answered = false
      response = ""
      while not answered
        response = @socket.gets.chomp
        #puts "#{@self_id}: #{response}"
        if response.start_with? "message "
          tmp = response.split ','
          on_broadcast_received(tmp[1], tmp[0].split(' ')[1].to_i)
        elsif response.start_with? "elevation en cours"
          on_ritual_started
        elsif response.start_with? "niveau actuel :"
          @level = response.split(':')[1].to_i
          on_ritual_completed @level
          answered = true
        elsif response == "mort"
          @dead = true
          Thread.exit
        else
          answered = true
        end
        break if only_one
      end
      response
    end

    def on_ritual_started
      #Override me !
    end

    def on_ritual_completed(new_level)
      #puts "Now: level #{new_level}"
      #Override me !
    end

    def on_broadcast_received(msg, direction)
      #Override me !
    end

    def reduce_hunger(amount)
      @food -= amount
    end

    def move_towards(coordinates)
      coordinates[1].times do
        do_action "avance"
      end
      turn_to = if (coordinates[0] > 0)
                  "droite"
                elsif (coordinates[0] < 0)
                  "gauche"
                else
                  nil
                end
      do_action turn_to unless turn_to.nil?
      coordinates[0].abs.times do
        do_action "avance"
      end
      if coordinates[1] < 0
        if turn_to.nil?
          do_action "gauche"
          do_action "gauche"
        else
          do_action turn_to
        end
        coordinates[1].abs.times do
          do_action "avance"
        end
      end
    end

    def translate_vision_to_map(index)
      ret = [0, 0]
      limit = 1
      index.times do
        ret[0] += 1
        if ret[0] == limit 
          ret[0] *= -1
          ret[1] += 1
          limit += 1
        end
      end
      ret
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

    def gather_item(item)
      pos = find_item(item)
      if not pos.nil?
        move_towards(pos)
        return pickup(item)
      end
      false
    end

    def available_slots
      do_action("connect_nbr").to_i
    end
    alias prendre pickup 
    alias ritual incantation
    alias see voir
    alias inventaire inventory
  end

  def self.main(trantorien)
    options = self.parse
    threads = []
    loop do
      tt = trantorien.new options[:team], options[:hostname], options[:port]
      if not tt.dead?
        threads << Thread.new { tt.process } 
      end
      sleep options[:delay]
    end
    threads.each { |thr| thr.join }
  end

  def self.parse
    options = {:delay => 1, :port => 8080, :hostname => "localhost"}
    OptionParser.new do |parser|
      parser.banner = "Usage: #{File.basename($0)} -t team [-p port] [-h hostname] [-d delay]"

      parser.on("-t", "--t TEAM", String, "Player team")
      parser.on("-d", "--delay SECONDS", Float, "Attempt connecting each SECONDS seconds. Defaults to 1. Can take decimal values.")
      parser.on("-p", "--port PORT", Integer, "Port number, 8080 by default")
      parser.on("-h", "--hostname HOST", Integer, "Hostname, localhost by default")
      parser.on("-h", "--help", "Display this help") { puts parser; exit }

    end.parse!(into: options)
    if options[:team].nil?
      exit
    end
    options 
  end
end
