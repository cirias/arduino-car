function configWifi(ssid, password)
  file.open('wificfg', 'w+')
  file.writeline(ssid)
  print('write ssid: ', ssid)
  file.writeline(password)
  print('write password: ', password)
  file.flush()
  file.close()
end

function connectWifi(callback)
  file.open('wificfg', 'r')
  ssid = file.readline()
  ssid = ssid:sub(1, -2)
  password = file.readline()
  password = password:sub(1, -2)
  print('ssid: ', ssid)
  print('password: ', password)
  file.close()

  wifi.setmode(wifi.STATION)
  print('set mode=STATION (mode='..wifi.getmode()..')')
  print('MAC: ',wifi.sta.getmac())
  wifi.sta.config(ssid, password)

  tmr.alarm(0, 1000, tmr.ALARM_AUTO, function()
    if wifi.sta.getip() == nil then
       print("Connecting to AP...\n")
    else
       ip, nm, gw=wifi.sta.getip()
       print("IP Info: \nIP Address: ",ip)
       print("Netmask: ",nm)
       print("Gateway Addr: ",gw,'\n')
       tmr.stop(0)

       callback()
    end
  end)
end
