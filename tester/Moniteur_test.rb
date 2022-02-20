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
    @commands = ["pin", "ppo", "plv"]
  end

  def teardown
    @tester.puts "set pdi #1"
    @tester.gets
    @tester.puts "set pdi #0"
  end

  def test_ppo_simple
    @tester.puts "get ppo #1"
    ret = @tester.gets
    @tester.puts "get ppo #1"
    ret2 = @tester.gets
    assert_equal ret, ret2
    @client.puts "avance"
    @client.gets
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

  def test_ppo_orientation
    @tester.puts "set ppo #1 0 0 2"
    assert_equal "ok\n", @tester.gets
    
    @tester.puts "get ppo #1"
    assert_equal "ppo #1 0 0 2\n", @tester.gets
    @client.puts "gauche"
    @client.gets
    @tester.puts "get ppo #1"
    assert_equal "ppo #1 0 0 1\n", @tester.gets

    @client.puts "gauche"
    @client.gets
    @tester.puts "get ppo #1"
    assert_equal "ppo #1 0 0 4\n", @tester.gets

    @client.puts "gauche"
    @client.gets
    @tester.puts "get ppo #1"
    assert_equal "ppo #1 0 0 3\n", @tester.gets

    @client.puts "gauche"
    @client.gets
    @tester.puts "get ppo #1"
    assert_equal "ppo #1 0 0 2\n", @tester.gets

    @client.puts "droite"
    @client.gets
    @tester.puts "get ppo #1"
    assert_equal "ppo #1 0 0 3\n", @tester.gets
  end

  def test_unknown_command
    @tester.puts "get cc"
    assert_equal "suc\n", @tester.gets
    @tester.puts "get titi"
    assert_equal "suc\n", @tester.gets
    @tester.puts "get "
    assert_equal "suc\n", @tester.gets
    @tester.puts "get poupou"
    assert_equal "suc\n", @tester.gets
    @tester.puts "get owrgbwoubgwr"
    assert_equal "suc\n", @tester.gets
    @tester.puts "get pini"
    assert_equal "suc\n", @tester.gets
    @tester.puts "get ppoopp"
    assert_equal "suc\n", @tester.gets
  end

  def test_bad_parameters
    @commands.each do |command|
    @tester.puts "get #{command} #5"
    assert_equal "sbp\n", @tester.gets

    @tester.puts "get #{command} 5"
    assert_equal "sbp\n", @tester.gets

    @tester.puts "get #{command} #-1"
    assert_equal "sbp\n", @tester.gets

    @tester.puts "get #{command} toto"
    assert_equal "sbp\n", @tester.gets

    @tester.puts "get #{command} #+5"
    assert_equal "sbp\n", @tester.gets
    end
  end
end
