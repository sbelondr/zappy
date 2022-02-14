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
    @found_player = nil
    @positions = {} 
  end

  def take_decision
    @goal = calc_converging
    if not @goal.nil? and @goal != [0, 0]
      move_towards @goal
      @goal = nil
      @found_player = find_item("PLAYER")
      if @found_player
        move_towards @found_player
      end
    else
      @found_player = find_item("PLAYER")
      if @found_player
        move_towards @found_player
      end
      do_action("gauche")
    end
    do_action("broadcast #{@self_id}: I AM HERE")
  end

  def sign(n)
    return 1 if n > 0
    return -1 if n < 0
    0
  end

  def calc_converging
    ret = [0, 0]
    zeros = 0
    @positions.each do |id, direction|
      if direction == 0
        zeros += 1
      else
        vec = translate_broadcast_to_vector(direction)
        ret[0] += vec[0]
        ret[1] += vec[1]
      end
    end
    if ret[0].abs <= zeros
      ret[0] = 0
    else
      ret[0] = ret[0] - (zeros * sign(ret[0]))
    end
    if ret[1].abs <= zeros
      ret[1] = 0
    else
      ret[1] = ret[1] - (zeros * sign(ret[1]))
    end
    puts "#{@self_id}: Going towards: #{ret}"
    ret
  end

  def on_broadcast_received(msg, direction)
    puts "#{@self_id}: I received #{msg} from #{direction} !!"

    id = msg.split(':')[0]
    if @positions[id] != direction
      @positions[id] = direction
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
