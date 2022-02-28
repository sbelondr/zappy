require 'socket'
require_relative '../clients/Trantorien.rb'

def connect(team)
  s = TCPSocket.new 'localhost', 8080
  s.gets
  s.puts team
  s.gets
  s
end
RSpec.describe 'Moving to a target direction', :client do
  before(:each) do
    @client = Client::Trantorien.new 'TOTO'
    @tester = connect 'TESTER'
  end
  after(:each) do
    @tester.puts "set pdi all"
  end

  context 'in a straight line' do
    it 'go straight in front' do
      @tester.puts 'set ppo #0 3 5 1'
      @tester.gets
      @client.move_towards([0, 2])
      @tester.puts 'get ppo #0'
      player_pos = @tester.gets
      expect(player_pos).to eq("ppo #0 3 3 1\n")
      @client.move_towards [0, 1]
      @tester.puts 'get ppo #0'
      player_pos = @tester.gets
      expect(player_pos).to eq("ppo #0 3 2 1\n")
    end
    it 'goes to the right' do
      @tester.puts 'set ppo #0 3 3 1'
      @tester.gets
      @client.move_towards [2, 0]
      @tester.puts 'get ppo #0'
      player_pos = @tester.gets
      expect(player_pos).to eq("ppo #0 5 3 2\n")
      @client.move_towards [1, 0]
      @tester.puts 'get ppo #0'
      player_pos = @tester.gets
      expect(player_pos).to eq("ppo #0 5 4 3\n")
    end
    it 'goes backwards' do
      @tester.puts 'set ppo #0 3 3 1'
      @tester.gets
      @client.move_towards [0, -2]
      @tester.puts 'get ppo #0'
      player_pos = @tester.gets
      expect(player_pos).to eq("ppo #0 3 5 3\n")
      @client.move_towards [0, -2]
      @tester.puts 'get ppo #0'
      player_pos = @tester.gets
      expect(player_pos).to eq("ppo #0 3 3 1\n")
    end
    it 'should goes to the left' do
      @tester.puts 'set ppo #0 3 3 1'
      @tester.gets
      @client.move_towards [-2, 0]
      @tester.puts 'get ppo #0'
      player_pos = @tester.gets
      expect(player_pos).to eq("ppo #0 1 3 4\n")
      @client.move_towards [-1, 0]
      @tester.puts 'get ppo #0'
      player_pos = @tester.gets
      expect(player_pos).to eq("ppo #0 1 4 3\n")
    end

  end
  context 'in diagonal' do
    it 'should go to the upper right' do
      @tester.puts 'set ppo #0 3 3 1'
      @tester.gets
      @client.move_towards [2, 2]
      @tester.puts 'get ppo #0'
      player_pos = @tester.gets
      expect(player_pos).to match(/ppo #0 5 1 \d\n/)
    end
    it 'should go to the lower left' do
      @tester.puts 'set ppo #0 3 3 1'
      @tester.gets
      @client.move_towards [-2, -2]
      @tester.puts 'get ppo #0'
      player_pos = @tester.gets
      expect(player_pos).to match(/ppo #0 1 5 \d\n/)
    end
    it 'should go to the lower right' do
      @tester.puts 'set ppo #0 3 3 1'
      @tester.gets
      @client.move_towards [2, -2]
      @tester.puts 'get ppo #0'
      player_pos = @tester.gets
      expect(player_pos).to match(/ppo #0 5 5 \d\n/)
    end
    it 'should go to the upper left' do
      @tester.puts 'set ppo #0 3 3 1'
      @tester.gets
      @client.move_towards [-2, 2]
      @tester.puts 'get ppo #0'
      player_pos = @tester.gets
      expect(player_pos).to match(/ppo #0 1 1 \d\n/)
    end

  end

end
RSpec.describe 'Checking if we can do the ritual', :ritual do
  before(:each) do
    @tester = connect 'TESTER'
    @clients = []
    6.times do |i|
      @clients.push Client::Trantorien.new('TOTO')
      @tester.puts "set ppo ##{i + 1} 5 5 1"
      @tester.gets
    end
  end
  after(:each) do
    @tester.puts "set pdi all"
  end

  context 'with enough materials' do
    it ': level 1' do 
      @tester.puts 'set bct 5 5 0 1 0 0 0 0 0'
      @tester.gets
      6.times do |i|
        vision = @clients[i].do_action "voir"
        expect(@clients[i].can_do_ritual vision, 1).to eq(true)
      end
    end
    it ': level 2' do 
      @tester.puts 'set bct 5 5 0 1 1 1 0 0 0'
      @tester.gets
      6.times do |i|
        vision = @clients[i].do_action "voir"
        expect(@clients[i].can_do_ritual vision, 2).to eq(true)
      end
    end
    it ': level 3' do 
      @tester.puts 'set bct 5 5 0 2 0 1 0 2 0'
      @tester.gets
      6.times do |i|
        vision = @clients[i].do_action "voir"
        expect(@clients[i].can_do_ritual vision, 3).to eq(true)
      end
    end
    it ': level 4' do 
      @tester.puts 'set bct 5 5 0 1 1 2 0 1 0'
      @tester.gets
      6.times do |i|
        vision = @clients[i].do_action "voir"
        expect(@clients[i].can_do_ritual vision, 4).to eq(true)
      end
    end
    it ': level 5' do 
      @tester.puts 'set bct 5 5 0 1 2 1 3 0 0'
      @tester.gets
      6.times do |i|
        vision = @clients[i].do_action "voir"
        expect(@clients[i].can_do_ritual vision, 5).to eq(true)
      end
    end
    it ': level 6' do 
      @tester.puts 'set bct 5 5 0 1 2 3 0 1 0'
      @tester.gets
      6.times do |i|
        vision = @clients[i].do_action "voir"
        expect(@clients[i].can_do_ritual vision, 6).to eq(true)
      end
    end
    it ': level 7' do 
      @tester.puts 'set bct 5 5 0 2 2 2 2 2 1'
      @tester.gets
      6.times do |i|
        vision = @clients[i].do_action "voir"
        expect(@clients[i].can_do_ritual vision, 7).to eq(true)
      end
    end
  end
  context 'with not enough materials' do
    it ': level 1' do 
      @tester.puts 'set bct 5 5 0 0 1 0 0 0 0'
      @tester.gets
      6.times do |i|
        vision = @clients[i].do_action "voir"
        expect(@clients[i].can_do_ritual vision, 1).to eq(false)
      end
    end
    it ': level 2' do 
      @tester.puts 'set bct 5 4 0 1 1 1 0 0 0'
      @tester.puts 'set bct 5 6 0 1 1 1 0 0 0'
      @tester.puts 'set bct 5 7 0 1 1 1 0 0 0'
      @tester.puts 'set bct 5 8 0 1 1 1 0 0 0'
      @tester.gets
      6.times do |i|
        vision = @clients[i].do_action "voir"
        expect(@clients[i].can_do_ritual vision, 2).to eq(false)
      end
    end
    it ': level 3' do 
      @tester.puts 'set bct 5 5 0 1 0 1 0 2 0'
      @tester.gets
      6.times do |i|
        vision = @clients[i].do_action "voir"
        expect(@clients[i].can_do_ritual vision, 3).to eq(false)
      end
    end
    it ': level 4' do 
      @tester.puts 'set bct 5 5 0 0 1 2 0 1 0'
      @tester.gets
      6.times do |i|
        vision = @clients[i].do_action "voir"
        expect(@clients[i].can_do_ritual vision, 4).to eq(false)
      end
    end
    it ': level 5' do 
      @tester.puts 'set bct 5 5 0 1 1 1 3 0 0'
      @tester.gets
      6.times do |i|
        vision = @clients[i].do_action "voir"
        expect(@clients[i].can_do_ritual vision, 5).to eq(false)
      end
    end
    it ': level 6' do 
      @tester.puts 'set bct 5 5 0 1 2 2 0 1 0'
      @tester.gets
      6.times do |i|
        vision = @clients[i].do_action "voir"
        expect(@clients[i].can_do_ritual vision, 6).to eq(false)
      end
    end
    it ': level 7' do 
      @tester.puts 'set bct 5 5 0 2 1 3 2 2 1'
      @tester.gets
      6.times do |i|
        vision = @clients[i].do_action "voir"
        expect(@clients[i].can_do_ritual vision, 7).to eq(false)
      end
  end

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
