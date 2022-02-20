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
    sleep 1
    @tester.puts "get ppo #1"
    ret = @tester.gets
    assert_not_equal ret, ret2
  end

  def test_pin_simple
    @tester.puts "set pin #1 clear"
    @tester.puts "get pin #1"
    @tester.puts "get ppo #1"
    assert_equal @tester.gets, "ok\n"
    inv = @tester.gets
    pos = @tester.gets.chomp.split
    assert_equal inv, "pin #1 #{pos[2]} #{pos[3]} 0 0 0 0 0 0 0\n"
  end

end
