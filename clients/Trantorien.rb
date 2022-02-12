# frozen_string_literal: true

class Trantorien
  def initialize(socket)
    @food = 126 * 10
    @inventory = [0, 0, 0, 0, 0, 0, 0]
    @socket = socket
  end

  def process
    puts "Override me!"
  end

  def pickup(item)
    ret = do_action("prendre #{item}")
    if ret == "ok"
      if item == "FOOD"
        @food += 126
        puts "Gained one food !! Current food: #{@food}"
      else
        @inventory[item_name_to_id(item)] += 1
      end
      return true
    else
      puts "Pickup failed for item #{item}!! WHAT DO I DO??!!"
      return false
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
    else
      puts "Pickup failed for item #{item}!! WHAT DO I DO??!!"
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
    rescue 
      puts "Connection to socket got screwed"
      puts "I don't know what to do...."
      puts "Goodbye!!!"
      exit
    end
    ret
  end

  def listen
    answered = false
    response = ""
    while not answered
      response = @socket.recv(999).chomp
      if response.start_with? "message "
        tmp = response.split ','
        on_broadcast_received(tmp[1], tmp[0].split(' ')[1])
      else
        answered = true
      end
    end
    response
  end

  def on_broadcast_received(msg, direction)
    puts "I received #{msg} from #{direction} !!"
  end

  def reduce_hunger(amount)
      @food -= amount
      puts "Getting hungrier ! Current hunger: #{@food}(-#{amount})!"
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

  #Returns coordinates to object if seen, nil otherwise
  def find_item(item)
    vision = []
    vision = do_action("voir").split(",")
    puts "#{vision}"
    vision.each_with_index do |area, index|
      if area.include? item 
        return translate_vision_to_map(index)
      end
    end
    return nil 
  end
end
