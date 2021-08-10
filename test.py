import serial
import time


ser = serial.Serial(port='/dev/ttyACM0', baudrate=345600, timeout=.1)
time.sleep(3);
i=0
while 2<9:
	while i<255:
		
		ser.write(bytes('<'+str(i)+',0,0,1>','utf8'))
		i=i+1
		time.sleep(0.001)
		

	
	while i>0:
		
		ser.write(bytes('<'+str(i)+',0,0,1>','utf8'))
		i=i-1
		time.sleep(0.001)

	i=0
	

	i=0	

ser.close()