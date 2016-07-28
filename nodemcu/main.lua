gpio.mode(5, gpio.OUTPUT)
gpio.mode(6, gpio.OUTPUT)
gpio.write(5, gpio.LOW)
gpio.write(6, gpio.LOW)

wifi.sta.config("ssid","password")

tmr.alarm(0, 1000, tmr.ALARM_AUTO, function()
  if wifi.sta.getip() == nil then
     print("Connecting to AP...\n")
  else
     ip, nm, gw=wifi.sta.getip()
     print("IP Info: \nIP Address: ",ip)
     print("Netmask: ",nm)
     print("Gateway Addr: ",gw,'\n')
     tmr.stop(0)

     dofile("server.lua")
  end
end)
