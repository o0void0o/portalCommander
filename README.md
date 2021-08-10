# Portal Commander
Skylanders Power Portal upgraded with an Arduino inside.
The result is a funky RGB light that may be controlled via the serial port.  

This was a very simple project. 

![Alt text](images/pic1.jpg?raw=true "Prototype1")

![Alt text](images/pic2.jpg?raw=true "Prototype1")

## Background

I don't game nor have any interest in Skylanders. I remember seeing the original portal and I really liked the way it looked and lit up.
I spotted a Wii version at the local pawn shop and basically got it for free. When plugged into a PC running windows the portal briefly lit up and then went dark. On Linux, it stayed lit. This pleased me and got me thinking.

## Teardown
The portal has 4 rubber feet. Remove the feet first. Remove the 4 screws under the feet. The base will now be able to separate. I took the top off but I guess it's not really necessary. Remove existing circuit board.

## New Hardware
To my surprise, there was a single led inside. It is a very bright SMD RGB LED. At that point, there were many possible hardware options. I opted to reuse the original LED. I removed the led from the original circuit board and placed it into my own. Not my finest work but it gets the job done. The side cutter then did some trimming and 2 cable ties later the Arduino was mounted inside. The base is then simply screwed back in place.

## LET THERE BE LIGHT
 The Arduino code is a simple serial command executor that waits for an RGB value to display. The idea is that the portal will be controlled via some other external program. In my use case, this will be a python script. From the python script, I send in the string <255,0,0> via the serial port and the portal will light up to max red.
 
 
 ## Use cases
 
 My primary use case for this is a visual notification system.EG a Jenkins server test job failed flash RED.
 Maby change colors based on CPU usage/temp.
 Make it flash to music.


