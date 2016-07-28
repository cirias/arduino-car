function startServer()
  sv = net.createServer(net.UDP)
  sv:on("receive",function(s,c)
    if c == "forward" then
      gpio.write(5, gpio.HIGH)
      gpio.write(6, gpio.LOW)
      gpio.write(7, gpio.LOW)
      gpio.write(8, gpio.LOW)
    elseif c == "backward" then
      gpio.write(5, gpio.LOW)
      gpio.write(6, gpio.HIGH)
      gpio.write(7, gpio.LOW)
      gpio.write(8, gpio.LOW)
    elseif c == "left" then
      gpio.write(5, gpio.LOW)
      gpio.write(6, gpio.LOW)
      gpio.write(7, gpio.HIGH)
      gpio.write(8, gpio.LOW)
    elseif c == "right" then
      gpio.write(5, gpio.LOW)
      gpio.write(6, gpio.LOW)
      gpio.write(7, gpio.LOW)
      gpio.write(8, gpio.HIGH)
    else
      gpio.write(5, gpio.LOW)
      gpio.write(6, gpio.LOW)
      gpio.write(7, gpio.LOW)
      gpio.write(8, gpio.LOW)
    end
  end) 
  sv:listen(4567)
end
