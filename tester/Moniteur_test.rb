# frozen_string_literal: true

require 'socket'
require 'test/unit/assertions'
require 'test/unit'
include Test::Unit::Assertions

class MoniteurCommandTester < Test::Unit::TestCase
  def setup 
    @tester = TCPSocket.new 'localhost', 8080
    @tester.gets
    @tester.puts "TESTER"
    @tester.gets
    @client = TCPSocket.new 'localhost', 8080
    @client.gets
    @client.puts "TOTO"
    @client.gets
    @client.gets
  end

  def teardown
    @tester.puts "set pdi #1"
    puts "set pdi #1"
    @tester.gets
    puts "set pdi #0"
    @tester.puts "set pdi #0"
  end

  def test_ppo_simple
    @tester.puts "get ppo #1"
    ret = @tester.gets
    @tester.puts "get ppo #1"
    ret2 = @tester.gets
    assert_equal ret, ret2
    @client.puts "avance"
    sleep 1
    @tester.puts "get ppo #1"
    ret = @tester.gets
    assert_not_equal ret, ret2
  end

  def test_pin_simple
    @tester.puts "set pin #1 clear"
    assert_equal "ok\n", @tester.gets
    @tester.puts "get pin #1"
    inv = @tester.gets
    @tester.puts "get ppo #1"
    pos = @tester.gets.chomp.split
    assert_equal "pin #1 #{pos[2]} #{pos[3]} 0 0 0 0 0 0 0\n", inv

    @tester.puts "set pin #1 1 2 3 4 5 6 7"
    assert_equal @tester.gets, "ok\n"
    @tester.puts "get pin #1"
    inv = @tester.gets
    assert_equal "pin #1 #{pos[2]} #{pos[3]} 1 2 3 4 5 6 7\n", inv
  end

end
