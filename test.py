import serial
import time

#Simple Red Led flasher
ser = serial.Serial(port='/dev/ttyACM0', baudrate=345600, timeout=.1)
time.sleep(3);

i=0
while 1:
	while i<255:
		
		ser.write(bytes('<'+str(i)+',0,0>','utf8'))
		i=i+1
		time.sleep(0.001)
	
	while i>0:
		
		ser.write(bytes('<'+str(i)+',0,0>','utf8'))
		i=i-1
		time.sleep(0.001)

	i=0

ser.close()