# frozen_string_literal: true

require "./Trantorien.rb"

class Leveler < Client::Trantorien
  def initialize(*args)
    super
    @needed = get_ritual_cost(1)
    @timer = 20
    @firstgen = true
  end

  def take_decision
    incantation
    unless @timer <= 0
      @timer -= 1
    end
    if @timer == 0 and @firstgen
      do_action "fork"
      do_action "fork"
      do_action "fork"
      do_action "fork"
      do_action "fork"
      @timer -= 1
    end
    if @answer
      broadcast "Oh, hello"
      @answer = false
    end
  end

  def on_ritual_started
    puts "#{broadcast_prefix}Ritual started!"
  end

  def on_ritual_completed(new_level)
    puts "#{broadcast_prefix}Incantation finished!!"
  end

  def broadcast_prefix
    "#{@self_id}:#{@level}:"
  end

  def on_broadcast_received(msg, direction)
    if @level > 1
      @answer = true
    end
    if msg == "Oh, hello" and @level == 1
      @firstgen = false
      puts "Not a first gen!"
    end
    puts "#{broadcast_prefix}Received broadcast: #{msg.inspect}!"
  end

  def starter
    puts "#{broadcast_prefix}Hello World!"
  end
end

Client::main Leveler
