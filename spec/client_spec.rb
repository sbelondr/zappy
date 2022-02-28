require 'socket'
require_relative '../clients/Trantorien.rb'

def connect(team)
  s = TCPSocket.new 'localhost', 8080
  s.gets
  s.puts team
  s.gets
  s.gets
  s
end
RSpec.describe 'Moving to a target direction' do
  before(:each) do
    @client = connect 'TOTO'
    @tester = connect 'TESTER'
  end
  after(:each) do
    @tester.puts "set pdi all"
  end

  context 'in a straight line' do

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
