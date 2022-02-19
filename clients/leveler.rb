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
    @possible_mode = [:foraging, :converging]
  end

  def foraging
    puts "Currently foraging!!"
    gather_item "FOOD"
    if gather_item "LINEMATE"
      do_action "broadcast #{broadcast_prefix}GATHERED LINEMATE"
      @mode = :converging
    else
      do_action "avance"
    end
  end

  def converging
    puts "Currently converging!!"
    if not @king
      if @with_king
        if @inventory[1] > 0
          do_action "pose LINEMATE"
        end
        listen true
      else
        if @goal != [0, 0]
          move_towards @goal
          @goal = [0, 0]
        else
          listen true
        end
      end
    else
      do_action("broadcast #{@self_id}: I AM HERE")
      if @inventory[1] > 0
        pose "LINEMATE"
      else
        vision = do_action "voir"
        if quantity_of("PLAYER", vision) > 5 and quantity_of("LINEMATE", vision) > 0
          puts "#{@self_id}: Starting incantation !!"
          do_action "incantation"
        end
      end
      puts "#{@self_id} sent a broadcast!"
    end
  end

  def take_decision
    if @mode == :foraging
      foraging
    else
      converging
    end
  end

  def broadcast_prefix
    "#{@self_id}:#{@level}:"
  end

  def on_broadcast_received(msg, direction)
    puts "#{@self_id}: I received >#{msg}< from #{direction} !! King status: #{@king}"

    info = msg.split(':')
    id = info[0].to_i
    if id > @king_id
      @king_id = id
      @king = false
      @with_king = false
    end
    if id == @king_id
      @goal = translate_broadcast_to_vector direction.to_i
      if direction == 0
        puts "CURRENTLY IN PLACE"
        @with_king = true
      end
    end
    if info[2] == "GATHERED LINEMATE"
      @communal_inventory[1] += 1
      @mode = :converging
    end
  end

  def starter
    do_action "broadcast #{broadcast_prefix}HELLO WORLD"
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

Client::main Leveler
