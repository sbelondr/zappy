# frozen_string_literal: true

require 'socket'
require 'test/unit/assertions'
require 'test/unit'
include Test::Unit::Assertions

class MoniteurTriggerTest < Test::Unit::TestCase
  def setup 
    @tester = TCPSocket.new 'localhost', 8080
    @tester.gets
    @tester.puts "TESTER"
    @tester.gets
    @tester.puts "set tac 6"
    @tester.gets
    @client = TCPSocket.new 'localhost', 8080
    @client.gets
    @client.puts "TOTO"
    @client.gets
    @client.gets
    @graphic = TCPSocket.new 'localhost', 8080
    @graphic.gets
    @graphic.puts "GRAPHIC"
    until @graphic.gets.start_with? "pnw"
    end
    @graphic.gets
    @graphic.gets
  end

  def teardown
    @tester.puts "set edi all"
    @tester.gets
    @tester.puts "set pdi all"
  end

  def test_client_connexion
    client2 = TCPSocket.new 'localhost', 8080
    client2.puts "TOTO"
    client2.gets
    client2.gets
    @tester.puts "get ppo #3"
    pos = @tester.gets.split
    assert_equal "pnw #3 #{pos[2]} #{pos[3]} #{pos[4]} 1 TOTO", @graphic.gets.chomp
    client3 = TCPSocket.new 'localhost', 8080
    client3.puts "TOTO"
    client3.gets
    client3.gets
    @tester.puts "get ppo #4"
    pos = @tester.gets.split
    assert_equal "pnw #4 #{pos[2]} #{pos[3]} #{pos[4]} 1 TOTO", @graphic.gets.chomp
    @tester.puts "set pdi #4"
    @tester.gets 
    @tester.puts "set pdi #3"
    @tester.gets 
  end

  def test_client_fork
    @tester.puts "get ppo #1"
    pos = @tester.gets.split
    @client.puts "fork"
    assert_equal "pfk #1\n", @graphic.gets 
    @client.gets
    assert_equal "enw #0 #1 #{pos[2]} #{pos[3]}\n", @graphic.gets

    @client.puts "fork"
    assert_equal "pfk #1\n", @graphic.gets 
    @client.gets
    assert_equal "enw #1 #1 #{pos[2]} #{pos[3]}\n", @graphic.gets
  end

  def test_client_eggs
    @tester.puts "set ppo #1 0 0 1"
    assert_equal "ok\n", @tester.gets
    @graphic.gets

    @client.puts "fork"
    @graphic.gets
    @client.gets
    @graphic.gets

    client2 = TCPSocket.new 'localhost', 8080
    client2.puts "TOTO"

    assert @graphic.gets.start_with? "pnw"

    assert_equal "eht #0\n", @graphic.gets
    assert_equal "edi #0\n", @graphic.gets

    @tester.puts "set tac 1"
    assert_equal "ok\n", @tester.gets

    client3 = TCPSocket.new 'localhost', 8080

    @client.puts "fork"
    @graphic.gets
    @client.gets
    @graphic.gets

    assert_equal "eht #0\n", @graphic.gets
    client3.puts "TOTO"
    assert_equal "ebo #0\n", @graphic.gets
    @tester.puts "get ppo #4"
    pos = @tester.gets.split
    assert_equal "pnw #4 0 0 #{pos[4]} 1 TOTO\n", @graphic.gets
    @tester.puts "set pdi #4"
    @tester.gets
    @tester.puts "set pdi #3"
    @tester.gets
  end
end
