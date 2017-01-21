from gpiozero import DigitalOutputDevice, PWMOutputDevice

class Motor:
    def __init__(self, ain1=None, ain2=None, bin1=None, bin2=None, pwma=None, pwmb=None):
        print("init")
        self.ain1 = DigitalOutputDevice(ain1, initial_value=False)
        self.ain2 = DigitalOutputDevice(ain2, initial_value=False)
        self.bin1 = DigitalOutputDevice(bin1, initial_value=False)
        self.bin2 = DigitalOutputDevice(bin2, initial_value=False)
        self.pwma = PWMOutputDevice(pwma, initial_value=.5)
        self.pwmb = PWMOutputDevice(pwmb, initial_value=.5)

    def stop(self):
        print("stop")
        self.ain1.off()
        self.ain2.off()
        self.bin1.off()
        self.bin2.off()

    def forward():
        print("forward")
        self.ain1.on()
        self.ain2.off()
        self.bin1.on()
        self.bin2.off()

    def backward():
        print("backward")
        self.ain1.off()
        self.ain2.on()
        self.bin1.off()
        self.bin2.on()

    def turn_left():
        print("turn_left")
        self.ain1.off()
        self.ain2.on()
        self.bin1.on()
        self.bin2.off()

    def turn_right():
        print("turn_right")
        self.ain1.on()
        self.ain2.off()
        self.bin1.off()
        self.bin2.on()
