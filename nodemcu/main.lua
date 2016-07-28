dofile('default.lua')
dofile('wifi.lua')
dofile('server.lua')

setDefault()

connectWifi(function()
  startServer()
end)
