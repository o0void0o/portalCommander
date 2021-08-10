import serial
import time
import psutil

## Simple CPU usage monitor.
ser = serial.Serial(port='/dev/ttyACM0', baudrate=345600, timeout=.1)
time.sleep(3);
i=0
while 1:
	x = psutil.cpu_percent()
	if x<30:
		ser.write(bytes('<0,255,0>','utf8'))
	
	if x>50 and x<70:
		ser.write(bytes('<255,255,0>','utf8'))

	if x>70:
		ser.write(bytes('<255,0,0>','utf8'))

	time.sleep(0.1)
ser.close()