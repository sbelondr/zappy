require 'socket'

RSpec.describe 'Connecting to server' do
  def connect
    TCPSocket.new 'localhost', 8080
  end
  before(:example) do
    @client = connect
    @client2 = connect
    @graphic = connect
    @tester = connect
  end
  it 'says BIENVENUE' do
    expect(@client.gets).to eq("BIENVENUE\n")
  end

  context 'after connecting' do
    before(:example) do
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
    end
    it 'properly connects good team' do
      ret = @client.gets
      expect(ret).to be_a(String)
      expect(ret).not_to eq("0\n")
      expect(ret.chomp).to match(/[\d]+/)
      ret = @client.gets
      expect(ret).to be_a(String)
      expect(ret.chomp).to match(/[\d]+ [\d]+/)
    end
    it 'properly connects graphics' do
      ret = @graphic.gets
      expect(ret).to be_a(String)
      expect(ret.chomp).to match(/msz [\d]+ [\d]+/)
    end
    it 'properly connects tester' do
      ret = @tester.gets
      expect(ret).to be_a(String)
      expect(ret.chomp).to eq('Test mode enabled. Welcome.')
    end
  end
end
