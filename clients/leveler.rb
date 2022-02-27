# frozen_string_literal: true

require "./Trantorien.rb"

class Leveler < Client::Trantorien
  def initialize(*args)
    super
    @goal = [0, 0]
    @found_player = nil
    @king = true 
    @king_id = @self_id.to_i
    @with_king = true 
    @mode = :foraging
    @communal_inventory = [0, 0, 0, 0, 0, 0, 0]
    @needed = get_ritual_cost(1)
    @possible_mode = [:foraging, :converging, :wait]
  end

  def foraging
    puts "#{broadcast_prefix}Currently foraging!!"
    gather_item "FOOD"
    1..6.times do |i|
      if @communal_inventory[i] < @needed[i]
        item_name = id_to_item_name i
        if gather_item item_name
          do_action "broadcast #{broadcast_prefix}GATHERED #{item_name}"
        end
      end
    end
    do_action "avance"
  end

  def converging
    #puts "#{broadcast_prefix}Currently converging!!"
    if not @king
      if @with_king
        pose_tout
        puts "#{broadcast_prefix}with king"
        listen true
      else
        if @goal != [0, 0]
          puts  "#{broadcast_prefix}moving towards king"
          move_towards @goal
          @goal = [0, 0]
        else
          listen true
        end
      end
    else
      do_action("broadcast #{broadcast_prefix}CONVERGING")
      pose_tout
      vision = do_action "voir"
      if quantity_of("PLAYER", vision) > 4 and can_do_ritual(vision, @level)
        puts "#{broadcast_prefix}Starting incantation !!"
        do_action "incantation"
      else
        puts "#{broadcast_prefix}Not enough to begin"
        puts "#{broadcast_prefix}There is only #{quantity_of "PLAYER", vision} players!"
      end
    end
  end

  def on_ritual_started
    @mode = :wait
    puts "#{broadcast_prefix}Now waiting !"
  end

  def on_ritual_completed(new_level)
    @mode = :foraging
    @communal_inventory = @inventory.dup
    @needed = get_ritual_cost new_level
    puts "#{broadcast_prefix}Incantation finished!!"
    puts "Inventory: #{@communal_inventory}, needed: #{@needed}"
  end

  def pose_tout
    1..6.times do |i|
      @inventory[i].times do 
        pose id_to_item_name(i)
      end
    end
  end

  def take_decision
    if @mode == :foraging
      foraging
    elsif @mode == :converging
      converging
    elsif @mode == :wait
      listen true
    else
      puts "FATAL ERROR"
    end
  end

  def broadcast_prefix
    "#{@self_id}:#{@level}:"
  end

  def enough_for_ritual
      enough = true
      1..6.times do |i|
        puts "#{broadcast_prefix}#{@communal_inventory[i]} < #{@needed[i]}"
        return false if @communal_inventory[i] < @needed[i]
      end
      true
  end

  def on_broadcast_received(msg, direction)
    #puts "#{@self_id}: I received >#{msg}< from #{direction} !! King status: #{@king}"

    info = msg.split(':')
    id = info[0].to_i
    if (info[1].to_i != @level)
      puts "#{broadcast_prefix}ignored a broadcast because it wasnt my level"
      return
    end
    if id > @king_id
      @king_id = id
      @king = false
      @with_king = false
      puts "#{broadcast_prefix}NEW KING WITH #{id}"
    end
    if id == @king_id
      @goal = translate_broadcast_to_vector direction.to_i
      if direction == 0
        @with_king = true
      else
        @with_king = false
      end
    end
    if info[2].start_with? "GATHERED "
      @communal_inventory[item_name_to_id info[2].split[1]] += 1
      if enough_for_ritual
        puts "#{broadcast_prefix}Converging"
        puts "#{broadcast_prefix}#{@communal_inventory}"
        #do_action "broadcast #{broadcast_prefix}CONVERGING"
        @mode = :converging
      end
    elsif info[2] == "HELLO WORLD"
      if id == @king_id and @mode == :converging
        #do_action "#{broadcast_prefix}CONVERGING"
      end
    elsif info[2] == "CONVERGING"
      @mode = :converging
    end
  end

  def starter
    do_action "broadcast #{broadcast_prefix}HELLO WORLD"
  end
end

Client::main Leveler
