require 'socket'

def putget(socket, msg)
  socket.puts msg
  socket.gets
end
RSpec.describe 'Connecting to server' do
  def connect
    TCPSocket.new 'localhost', 8080
  end
  before(:each) do
    @client = connect
    @client2 = connect
    @graphic = connect
    @tester = connect
  end
  after(:each) do
    @cleanup = connect
    @cleanup.gets
    @cleanup.puts "TESTER"
    @cleanup.gets
    @cleanup.puts "set pdi all"
  end
  it 'says BIENVENUE' do
    expect(@client.gets).to eq("BIENVENUE\n")
  end

  context 'after connecting' do
    before(:each) do
      @client.gets
      @client.puts 'TOTO'
      @client2.gets
      @client2.puts 'badteam'
      @tester.gets
      @tester.puts 'TESTER'
      @graphic.gets
      @graphic.puts 'GRAPHIC'
    end
    it 'does not connect bad team' do
      ret = @client2.gets
      expect(ret).to be_a(String)
      expect(ret).to eq("0\n")
      @tester.gets
    end
    it 'properly connects good team' do
      ret = @client.gets
      expect(ret).to be_a(String)
      expect(ret).not_to eq("0\n")
      expect(ret.chomp).to match(/[\d]+/)
      ret = @client.gets
      expect(ret).to be_a(String)
      expect(ret.chomp).to match(/[\d]+ [\d]+/)
      @tester.gets
    end
    it 'properly connects graphics' do
      ret = @graphic.gets
      expect(ret).to be_a(String)
      expect(ret.chomp).to match(/msz [\d]+ [\d]+/)
      @tester.gets
    end
    it 'properly connects tester' do
      ret = @tester.gets
      expect(ret).to be_a(String)
      expect(ret.chomp).to eq('Test mode enabled. Welcome.')
    end
  end
end

RSpec.describe 'Using the TESTER' do
  def connect
    TCPSocket.new 'localhost', 8080
  end


  before(:each) do
    @client = connect
    @client2 = connect
    @graphic = connect
    @tester = connect
    @client.gets
    @client.puts 'TOTO'
    @client.gets
    @client.gets
    @client2.gets
    @client2.puts 'TOTO'
    @client2.gets
    @client2.gets
    @tester.gets
    @tester.puts 'TESTER'
    @tester.gets
    @graphic.gets
    @graphic.puts 'GRAPHIC'
  end
  after(:each) do
    @cleanup = connect
    @cleanup.gets
    @cleanup.puts "TESTER"
    @cleanup.gets
    @cleanup.puts "set edi all"
    @cleanup.gets
    @cleanup.puts "set pdi all"
  end
  context 'with well formatted input' do
    it 'can set the position of a player' do
      @tester.puts "set ppo #0 0 0 1"
      expect(@tester.gets).to eq("ok\n")
      @tester.puts "get ppo #0"
      expect(@tester.gets).to eq("ppo #0 0 0 1\n")
      @tester.puts "set ppo #1 5 5 3"
      expect(@tester.gets).to eq("ok\n")
      @tester.puts "get ppo #1"
      expect(@tester.gets).to eq("ppo #1 5 5 3\n")
    end
    it 'can set the inventory of a player' do
      @tester.puts "set pin #0 clear"
      expect(@tester.gets).to eq("ok\n")
      @tester.puts "get pin #0"
      expect(@tester.gets).to match(/pin #0 \d+ \d+ 0 0 0 0 0 0 0\n/)
      @tester.puts "set pin #1 1 2 3 4 5 6 7"
      expect(@tester.gets).to eq("ok\n")
      @tester.puts "get pin #1"
      expect(@tester.gets).to match(/pin #1 \d+ \d+ 1 2 3 4 5 6 7\n/)
    end
    it 'can set the time unit of the server' do
      expect(putget @tester, 'set sst 50').to eq("sgt 50\n")
      expect(putget @tester, 'sgt').to eq("sgt 50\n")
    end
    it 'can set the allowed clients at start amount of the server' do
      expect(putget @tester, 'set tac 50').to eq("ok\n")
      expect(putget @tester, 'get tac').to eq("tac 50\n")
    end
    it 'can set the maximum amount of clients allowed per team on the server' do
      expect(putget @tester, 'set mac 50').to eq("ok\n")
      expect(putget @tester, 'get mac').to eq("mac 50\n")
    end
    it 'can set items on the ground' do
      expect(putget @tester, 'set bct 5 3 clear').to eq("ok\n")
      expect(putget @tester, 'set bct 2 6 1 2 3 4 5 6 7').to eq("ok\n")
      expect(putget @tester, 'get bct 5 3').to eq("bct 5 3 0 0 0 0 0 0 0\n")
      expect(putget @tester, 'get bct 2 6').to eq("bct 2 6 1 2 3 4 5 6 7\n")
    end
    it 'can clear the whole map' do
      @tester.puts 'get msz'
      ret = @tester.gets
      expect(ret).to match(/msz \d+ \d+/)
      size = ret.split[1..2].collect(&:to_i)
      expect(putget @tester, 'set mct clear').to eq("ok\n")
      @tester.puts 'get mct'
      @size[0].times do |x|
        @size[1].times do |y|
          expect(@tester.gets).to eq("bct #{y} #{x} 0 0 0 0 0 0 0\n")
        end
      end
    end
    it 'can kill players' do
      expect(putget @tester, 'set pdi #0').to eq("ok\n")
    end
    it 'can create eggs' do
      expect(putget @tester, 'set enw 5 4 TOTO').to eq("ok\n")
      expect(putget @tester, 'set edi #0').to eq("ok\n")
    end
  end
  context 'with bad inputs' do
    it 'answers suc to unknown commands' do
      expect(putget @tester, 'toto' ).to eq("suc\n")
      expect(putget @tester, 'get toto' ).to eq("suc\n")
      expect(putget @tester, 'set pini' ).to eq("suc\n")
      expect(putget @tester, 'set ppopp' ).to eq("suc\n")
      expect(putget @tester, 'get mszs' ).to eq("suc\n")
      expect(putget @tester, 'get pini' ).to eq("suc\n")
    end

    it 'answers sbp to bad parameters' do
      expect(putget(@tester, 'set ppo #6 0 0 3')).to eq("sbp\n")
      expect(putget(@tester, 'set ppo #-1 0 0 3')).to eq("sbp\n")
      expect(putget(@tester, 'set ppo #a 0 0 3')).to eq("sbp\n")
      expect(putget(@tester, 'set ppo #0b 0 0 3')).to eq("sbp\n")
      expect(putget(@tester, 'set ppo #0 a 0 3')).to eq("sbp\n")
      expect(putget(@tester, 'set ppo #0 0 a 3')).to eq("sbp\n")
      expect(putget(@tester, 'set ppo #0 0 0 0')).to eq("sbp\n")
      expect(putget(@tester, 'set ppo #0 0 0 5')).to eq("sbp\n")
    end
  end
end

RSpec.describe 'Using the CLIENT' do
  def connect
    TCPSocket.new 'localhost', 8080
  end
  before(:each) do
    @client = connect
    @client2 = connect
    @graphic = connect
    @tester = connect
    @client.gets
    @client.puts 'TOTO'
    @client.gets
    @client.gets
    @client2.gets
    @client2.puts 'TOTO'
    @client2.gets
    @client2.gets
    @tester.gets
    @tester.puts 'TESTER'
    @tester.gets
    @graphic.gets
    @graphic.puts 'GRAPHIC'
    @tester.puts 'get msz'
    @map_size = @tester.gets.split[1..2].collect &:to_i
  end
  after(:each) do
    @cleanup = connect
    @cleanup.gets
    @cleanup.puts "TESTER"
    @cleanup.gets
    @cleanup.puts "set pdi all"
  end
  context 'Going forward' do
    context 'in the middle of the map' do
      it 'goes north' do
        @tester.puts "set ppo #0 5 5 1"
        @tester.gets
        @client.puts "avance"
        expect(@client.gets).to eq("ok\n")
        @tester.puts "get ppo #0"
        expect(@tester.gets).to eq("ppo #0 5 4 1\n")
      end
      it 'goes east' do
        @tester.puts "set ppo #0 5 5 2"
        @tester.gets
        @client.puts "avance"
        expect(@client.gets).to eq("ok\n")
        @tester.puts "get ppo #0"
        expect(@tester.gets).to eq("ppo #0 6 5 2\n")
      end
      it 'goes west' do
        @tester.puts "set ppo #0 5 5 4"
        @tester.gets
        @client.puts "avance"
        expect(@client.gets).to eq("ok\n")
        @tester.puts "get ppo #0"
        expect(@tester.gets).to eq("ppo #0 4 5 4\n")
      end
      it 'goes south' do
        @tester.puts "set ppo #0 5 5 3"
        @tester.gets
        @client.puts "avance"
        expect(@client.gets).to eq("ok\n")
        @tester.puts "get ppo #0"
        expect(@tester.gets).to eq("ppo #0 5 6 3\n")
      end
    end
    context 'on the borders of the map' do
      it 'goes north' do
        @tester.puts "set ppo #0 0 0 1"
        @tester.gets
        @client.puts "avance"
        expect(@client.gets).to eq("ok\n")
        @tester.puts "get ppo #0"
        expect(@tester.gets).to eq("ppo #0 0 #{@map_size[1] - 1} 1\n")
      end
      it 'goes east' do
        @tester.puts "set ppo #0 #{@map_size[0] - 1} 5 2"
        @tester.gets
        @client.puts "avance"
        expect(@client.gets).to eq("ok\n")
        @tester.puts "get ppo #0"
        expect(@tester.gets).to eq("ppo #0 0 5 2\n")
      end
      it 'goes west' do
        @tester.puts "set ppo #0 0 5 4"
        @tester.gets
        @client.puts "avance"
        expect(@client.gets).to eq("ok\n")
        @tester.puts "get ppo #0"
        expect(@tester.gets).to eq("ppo #0 #{@map_size[0] - 1} 5 4\n")
      end
      it 'goes south' do
        @tester.puts "set ppo #0 5 #{@map_size[1] - 1} 3"
        @tester.gets
        @client.puts "avance"
        expect(@client.gets).to eq("ok\n")
        @tester.puts "get ppo #0"
        expect(@tester.gets).to eq("ppo #0 5 0 3\n")
      end
    end
  end

  context 'Making the client turn ' do
    it 'right' do
      @tester.puts "set ppo #0 0 0 1"
      @tester.gets
      @client.puts 'droite'
      expect(@client.gets).to eq("ok\n")
      @tester.puts 'get ppo #0'
      expect(@tester.gets).to eq("ppo #0 0 0 2\n")
      @client.puts 'droite'
      expect(@client.gets).to eq("ok\n")
      @tester.puts 'get ppo #0'
      expect(@tester.gets).to eq("ppo #0 0 0 3\n")
      @client.puts 'droite'
      expect(@client.gets).to eq("ok\n")
      @tester.puts 'get ppo #0'
      expect(@tester.gets).to eq("ppo #0 0 0 4\n")
      @client.puts 'droite'
      expect(@client.gets).to eq("ok\n")
      @tester.puts 'get ppo #0'
      expect(@tester.gets).to eq("ppo #0 0 0 1\n")
    end
    it 'left' do
      @tester.puts "set ppo #0 0 0 1"
      @tester.gets
      @client.puts 'gauche'
      expect(@client.gets).to eq("ok\n")
      @tester.puts 'get ppo #0'
      expect(@tester.gets).to eq("ppo #0 0 0 4\n")
      @client.puts 'gauche'
      expect(@client.gets).to eq("ok\n")
      @tester.puts 'get ppo #0'
      expect(@tester.gets).to eq("ppo #0 0 0 3\n")
      @client.puts 'gauche'
      expect(@client.gets).to eq("ok\n")
      @tester.puts 'get ppo #0'
      expect(@tester.gets).to eq("ppo #0 0 0 2\n")
      @client.puts 'gauche'
      expect(@client.gets).to eq("ok\n")
      @tester.puts 'get ppo #0'
      expect(@tester.gets).to eq("ppo #0 0 0 1\n")
    end
  end
end
