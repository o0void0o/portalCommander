# Portal Commander
Skylanders Power Portal upgraded with an Arduino inside.
The result is a funky RGB light that may be controlled via the serial port.  

![Alt text](images/pic1.jpg?raw=true "Prototype1")

![Alt text](images/pic2.jpg?raw=true "Prototype1")

## Background

I don't game nor do I have any interest in Skylanders. The original portal impressed me with its looks and I was curious to see what is inside of it.
Years later I spotted a Wii version at the local pawn shop and basically got it for free. When plugged into a PC running windows the portal will briefly light up and then go dark. On Linux, it stays lit. This pleased me and got me thinking of possible alternative uses for this thing.

## Teardown

The portal has 4 rubber feet. Remove the feet first. Remove the 4 screws under the feet. The base will now be able to separate. I took the top off but it's not necessary. Remove the existing circuit board with its USB cable. All RFID related hardware in the portal is of no importance to me. I simply removed it all.

## New Hardware

To my surprise, there was a single led inside. It is a very bright surface-mounted RGB LED. At that point, there were many possible hardware options. I opted to reuse the original LED, aka the easiest option. I drafted a veraboard prototype circuit and removed the RGB led from the original circuit board and placed it into my own. The board is not my finest work but it gets the job done. The side cutter then did some internal plastic trimming and 2 cable ties later the Arduino was mounted inside. The base is then simply screwed back in place.

Do note that the LED height is of top importance. Too high and it will not be defused anymore. Lower is better. Nothing is stopping you from being more creative and adding multiple LEDs.The effects would be crazy, but I opted for a more simple solution.

## LET THERE BE LIGHT

The process involves 2 parts. The Arduino enables an external driver program to light up the LEDS via its serial port. 

The Arduino code is a simple serial command executor that waits for an RGB formatted string to arrive. The idea is that the portal will be controlled via some other external program. In my use case, this will be a python script. The python script will send a command  eg: <255,0,0> via the serial port and the portal will light up to red.
Use cases
My primary use case for this is a visual notification system. I intend to use this to monitor a Jenkins test job. If it failed then the postal will flash RED.
I toyed with some other ideas like changing the color based on CPU usage/temp. Perhaps disco it up by making it flash to music. Maybe just hardcode some funky color cycles on the portal and use it as a display stand? I'm going to upgrade mine to include a knock sensor. Then I can get some input going opening up even more possibilities.

It is a simple project but there are so many interesting uses. Hope this inspires fellow hackers.


