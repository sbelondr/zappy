# frozen_string_literal: true

require "./Trantorien.rb"

if ARGV.empty?
  puts "You must pass the team name as first argument"
  exit 1
end

class Converging < Trantorien
  def initialize(*args)
    super
    @goal = nil
  end
  def take_decision
    if not @goal.nil?
      move_towards(@goal)
      @goal = find_item("PLAYER")
    else
      do_action("broadcast #{@self_id}: I AM HERE")
    end
  end

  def on_broadcast_received(msg, direction)
    puts "#{@self_id}: I received #{msg} from #{direction} !!"
    @goal = translate_broadcast_to_vector(direction)
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
