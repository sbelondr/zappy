require 'socket'
require_relative '../clients/Trantorien.rb'

def connect(team)
  s = TCPSocket.new 'localhost', 8080
  s.gets
  s.puts team
  s.gets
  s
end
RSpec.describe 'Moving to a target direction' do
  before(:each) do
    @client = Client::Trantorien.new 'TOTO'
    @tester = connect 'TESTER'
  end
  after(:each) do
    @tester.puts "set pdi all"
  end

  context 'in a straight line' do
    it 'goes straight in front' do
      @tester.puts 'set ppo #0 3 3 1'
      @tester.gets
      @client.move_towards [0, 2]
      @tester.puts 'get ppo #0'
      player_pos = @tester.gets
      expect(player_pos).to eq("ppo #0 3 1 1\n")
      @tester.puts 'set ppo #0 3 3 3'
      @tester.gets
      @client.move_towards [0, 2]
      @tester.puts 'get ppo #0'
      player_pos = @tester.gets
      expect(player_pos).to eq("ppo #0 3 3 3\n")
  end
    it 'goes to the left' do
      @tester.puts 'set ppo #0 3 3 1'
      @tester.gets
      @client.move_towards [2, 0]
      @tester.puts 'get ppo #0'
      player_pos = @tester.gets
      expect(player_pos).to eq("ppo #0 5 3 1\n")
      @client.move_towards [1, 0]
      @tester.puts 'get ppo #0'
      player_pos = @tester.gets
      expect(player_pos).to eq("ppo #0 6 3 1\n")
  end

  end
  context 'in diagonal' do

  end

end
RSpec.describe 'Doing ritual' do
  before(:each) do
    @client = connect 'TOTO'
    @client2 = connect 'TOTO'
    @client3 = connect 'TOTO'
    @client4 = connect 'TOTO'
    @client5 = connect 'TOTO'
    @client6 = connect 'TOTO'
    @client7 = connect 'TOTO'
    @tester = connect 'TESTER'
  end
  after(:each) do
    @tester.puts "set pdi all"
  end

  context 'With enough materials' do

  end
  context 'With not enough materials' do

  end
  context 'With not enough players' do

  end

end
