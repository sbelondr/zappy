# frozen_string_literal: true

require 'socket'

s = TCPSocket.new 'localhost', 8080
s.print 'gauche'
sleep(5)
s.print 'gauche'
sleep(5)
s.print 'voir'
sleep(5)
s.print 'avance'
puts s.recv(99)
s.print 'voir'
while lign = s.recv(99)
  s.print 'avance'
  puts s.recv(99)
  s.print 'voir'
end
