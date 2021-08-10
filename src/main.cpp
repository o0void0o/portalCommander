// (c) 2021 Etienne
// This code is licensed under MIT license (see LICENSE.txt for details)

#include <Arduino.h>
#include <SimpleTimer.h>

const byte numChars = 12; // max nr of chars expected.
const char cmdStartIndicator = '<';
const char cmdEndIndicator = '>';

char receivedChars[numChars];
char cmdToParse[numChars];
boolean incommingData = false;
byte incommingDataIndex = 0;

int _r = 0; // red 0-255 value
int _g = 0; // green 0-255 value
int _b = 0; // blue 0-255 value

int idleCounter = 0;
boolean newCmdToParse = false;
SimpleTimer timer;

void ledSaver(void)
{
   idleCounter++;
   //save that LED by turning it off after 1H of no activity.This might bite me later.
   if (idleCounter > (60 * 60))
   {
      _r = 0;
      _g = 0;
      _b = 0;
      idleCounter = 0;
   }
}

void setup(void)
{
   Serial.begin(345600);
   Serial.println("Send data in this format <255, 12, 50>");
   pinMode(9, OUTPUT);
   pinMode(10, OUTPUT);
   pinMode(11, OUTPUT);
   timer.setInterval(1000, ledSaver);
}

void getNewCommand()
{
   char currentChar;

   while (Serial.available() > 0 && !newCmdToParse)
   {
      currentChar = Serial.read();
      if (incommingData)
      {
         if (currentChar != cmdEndIndicator)
         {
            receivedChars[incommingDataIndex] = currentChar;
            incommingDataIndex++;
            if (incommingDataIndex >= numChars)
            {
               incommingDataIndex = numChars - 1;
            }
         }
         else
         {
            receivedChars[incommingDataIndex] = '\0'; // terminate the string
            incommingData = false;
            incommingDataIndex = 0;
            newCmdToParse = true;
         }
      }

      else if (currentChar == cmdStartIndicator)
      {
         incommingData = true;
      }
   }
}

//
// Splits the incomming serial data into RGB segments.
// It is expected to arive as <255,255,255>
//
void parseData()
{
   char *strtokIndx;

   strtokIndx = strtok(cmdToParse, ","); // get the 1st part - RED (0-255)
   _r = atoi(strtokIndx);

   strtokIndx = strtok(NULL, ","); // get the 2'd part - GREEN (0-255)
   _g = atoi(strtokIndx);

   strtokIndx = strtok(NULL, ","); // get the 3rd part - BLUE (0-255)
   _b = atoi(strtokIndx) / 5.1;    // my blue leds broken, sorz
}

void loop(void)
{
   timer.run();
   getNewCommand();
   if (newCmdToParse)
   {
      strcpy(cmdToParse, receivedChars);
      parseData();
      newCmdToParse = false;
      
      analogWrite(9, _r);
      analogWrite(10, _g);
      analogWrite(11, _b);

      idleCounter = 0;
   }
}