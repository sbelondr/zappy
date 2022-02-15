# frozen_string_literal: true

require "./Trantorien.rb"

if ARGV.empty?
  puts "You must pass the team name as first argument"
  exit 1
end

class Converging < Trantorien
  def initialize(*args)
    super
    @goal = [0, 0]
    @found_player = nil
    @king = true 
    @king_id = @self_id.to_i
  end

  def take_decision
    if not @king
      if @goal != [0, 0]
      puts "#{@self_id}: MOVING"
      end
      move_towards @goal
      @goal = [0, 0]
    else
      do_action("broadcast #{@self_id}: I AM HERE")
      puts "#{@self_id} sent a broadcast!"
    end
  end

  def on_broadcast_received(msg, direction)
    puts "#{@self_id}: I received >#{msg}< from #{direction} !! King status: #{@king}"

    id = msg.split(':')[0].to_i
    if id > @king_id
      @king_id = id
      @king = false
    end
    if id == @king_id
      @goal = translate_broadcast_to_vector direction.to_i
      puts "#{@self_id}: Going towards #{@goal}"
    end
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

main Converging, ARGV[0]
