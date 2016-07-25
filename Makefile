ARDMK_DIR         = /usr/share/arduino
# ARDUINO_DIR       = /usr/share/arduino

# USER_LIB_PATH    :=  ../libraries
ARDUINO_LIBS = PID

BOARD_TAG    = uno
# MONITOR_PORT = /dev/ttyACM*
# MONITOR_BAUDRATE  = 115200

# AVR_TOOLS_DIR     = /usr

# AVRDUDE          = /usr/bin/avrdude

# CXXFLAGS = --std=gnu++11 -fno-threadsafe-statics

include ${ARDMK_DIR}/Arduino.mk
