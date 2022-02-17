# frozen_string_literal: true

require 'socket'

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
      if not @dead
        take_decision
      else
        puts "i AM dead"
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

  def self.main(trantorien, team_name)
    threads = []
    main_player =  trantorien.new team_name
    loop do
      tt = trantorien.new team_name
      if not tt.dead?
        threads << Thread.new { loop { tt.process; break if tt.dead? } }
      end
      sleep 1
    end
    threads.each { |thr| thr.join }
  end
end
