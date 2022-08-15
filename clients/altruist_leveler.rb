# frozen_string_literal: true

require "./Trantorien.rb"

class Leveler < Client::Trantorien
  def initialize(*args)
    super
    @goal = [0, 0]
    @reached = false
    @mode = :foraging
    @needed = get_ritual_cost(1)
    @possible_mode = [:foraging, :converging, :wait, :waiting_for_ritual]
  end

  def foraging
    puts "#{broadcast_prefix}Currently foraging!!"
    puts "#{broadcast_prefix}Gathering food first..."
    if gather_item "nourriture"
      puts "Found food!"
    else
      puts "Found no food."
    end
    1..6.times do |i|
      if @inventory[i] < @needed[i]
        item_name = id_to_item_name i
        if gather_item item_name
          puts "#{broadcast_prefix}Found #{item_name}!"
        else
          puts "#{broadcast_prefix}Found no #{item_name}."
        end
        return if @mode != :foraging
        if enough_for_ritual
          broadcast "START RITUAL"
          broadcast "HERE"
          @mode = :waiting_for_ritual
          @reached = true
          puts "#{broadcast_prefix}ENOUGH FOR RITUAL"
        else
          puts "#{broadcast_prefix}Not enough for ritual"
        end
      end
    end
    do_action "avance"
  end

  def converging
    #puts "#{broadcast_prefix}Currently converging!!"
    if not @reached or not enough_for_ritual
      move_towards @goal
      @mode = :waiting_for_ritual if @goal == [0, 0]
      puts "#{broadcast_prefix}Moving to #@goal!!"
    else
      @mode = :waiting_for_ritual
    end
  end

  def generate_ritual
    pose_tout
    broadcast "HERE"
    vision = do_action "voir"
    if quantity_of("player", vision) > 5 and can_do_ritual(vision, @level)
      puts "#{broadcast_prefix}Starting incantation !!"
      incantation
    end
    puts "#{broadcast_prefix}Not enough to begin"
    puts "#{broadcast_prefix}There is only #{quantity_of "player", vision}/5 players!"
  end

  def waiting_for_ritual
    voir
    puts "#{broadcast_prefix}Waiting"
  end

  def on_ritual_started
    @mode = :wait
    puts "#{broadcast_prefix}Now waiting !"
  end

  def on_ritual_completed(new_level)
    @mode = :foraging
    @reached = false
    @needed = get_ritual_cost new_level
    puts "#{broadcast_prefix}Incantation finished!!"
  end

  def pose_tout
    1..6.times do |i|
      @inventory[i].times do 
        pose id_to_item_name(i)
      end
    end
  end

  def prendre_tout
    vision = do_action("voir").split(',')[0]
    vision.slice!(0)
    items = vision.split.filter {|a| a != "PLAYER"} 
    while items.size > 0
      item = current.split(" ").sample
      prendre item
      vision = do_action("voir"),split(',')[0]
      vision.slice!(0)
      items = current.split.filter {|a| a != "PLAYER"} 
    end
  end

  def take_decision
    if @mode == :foraging
      foraging
    elsif @mode == :converging
      converging
    elsif @mode == :wait
      listen true
    elsif @mode == :waiting_for_ritual
      waiting_for_ritual
    else
      puts "FATAL ERROR: Unknown mode: #@mode"
    end
  end

  def broadcast_prefix
    "#{@self_id}:#{@level}:"
  end

  def enough_for_ritual
    enough = true
    1..6.times do |i|
      return false if @inventory[i] < @needed[i]
    end
    true
  end

  def on_broadcast_received(msg, direction)
    info = msg.split(':')
    id = info[0].to_i
    if (info[1].to_i != @level)
      puts "#{broadcast_prefix}ignored a broadcast because it wasnt my level"
      return
    end
    if info[2].start_with? "START RITUAL"
      puts "#{broadcast_prefix}STARTING CONVERGING"
      @mode = :converging
    end
    if info[2].start_with? "HERE"
      @goal = translate_broadcast_to_vector direction
      @reached = direction.zero?
      if @mode != :converging && @mode != :waiting_for_ritual
        puts "ERROR: RECEIVED HERE FROM #{info[0]} OUT OF ORDER"
      end
      @mode = :converging if @mode != :waiting_for_ritual
    end
  end

  def starter
    broadcast "HELLO WORLD"
  end
end

Client::main Leveler
