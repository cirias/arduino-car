sv = net.createServer(net.UDP)
sv:on("receive",function(s,c)
  if c == "go\n" then
    gpio.write(5, gpio.HIGH)
    gpio.write(6, gpio.LOW)
  elseif c == "back\n" then
    gpio.write(5, gpio.LOW)
    gpio.write(6, gpio.HIGH)
  else
    gpio.write(5, gpio.LOW)
    gpio.write(6, gpio.LOW)
  end
end) 
sv:listen(4567)
