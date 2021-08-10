#include <Arduino.h>
#include <SimpleTimer.h>>

const byte numChars = 32;
char receivedChars[numChars];
char tempChars[numChars]; // temporary array for use when parsing
SimpleTimer timer;

// variables to hold the parsed data
char messageFromPC[numChars] = {0};
int _r = 0;
int _g = 0;
int _b = 0;
int _flash = 0;
float floatFromPC = 0.0;
bool tog = true;
bool demo_mode = false;
int counter = 0;

boolean newData = false;

String sdata = ""; // Initialised to nothing.
byte test, start;

void repeatMe(void)
{
   if (!demo_mode)
   {
      counter++;
   }

   if (counter > (60 * 60))
   {
      demo_mode = true;
      counter = 0;
   }
}
void setup(void)
{
   Serial.begin(345600);
   Serial.println("Enter data in this style <255, 12, 50,5000>,<red,green,blue,flash>");
   pinMode(9, OUTPUT);
   pinMode(10, OUTPUT);
   pinMode(11, OUTPUT);
   //timer.setInterval(1000, repeatMe);
}

void recvWithStartEndMarkers()
{
   static boolean recvInProgress = false;
   static byte ndx = 0;
   char startMarker = '<';
   char endMarker = '>';
   char rc;

   while (Serial.available() > 0 && newData == false)
   {

      rc = Serial.read();
      if (recvInProgress == true)
      {
         if (rc != endMarker)
         {
            receivedChars[ndx] = rc;
            ndx++;
            if (ndx >= numChars)
            {
               ndx = numChars - 1;
            }
         }
         else
         {
            receivedChars[ndx] = '\0'; // terminate the string
            recvInProgress = false;
            ndx = 0;
            newData = true;
         }
      }

      else if (rc == startMarker)
      {
         recvInProgress = true;
      }
   }
}

//============

void parseData()
{ // split the data into its parts

   char *strtokIndx; // this is used by strtok() as an index

   strtokIndx = strtok(tempChars, ","); // get the first part - the string
   _r = atoi(strtokIndx);               // copy it to messageFromPC

   strtokIndx = strtok(NULL, ","); // this continues where the previous call left off
   _g = atoi(strtokIndx);          // convert this part to an integer

   strtokIndx = strtok(NULL, ",");
   _b = atoi(strtokIndx) / 5.1; // my blue leds broken.

   strtokIndx = strtok(NULL, ",");

   if (strtokIndx != NULL)
   {
      _flash = atoi(strtokIndx);
   }
}
// void demo()
// {
//    if (demo_mode)
//    {
//       for (int i = 0; i < 150; i++)
//       {
//          analogWrite(9, i);
//          delay(2);
//       }
//    }
//    if (demo_mode)
//    {
//       delay(5000);
//       for (int i = 0; i < 50; i++)
//       {
//          analogWrite(11, i);
//          delay(30);
//       }
//    }
//    if (demo_mode)
//    {
//       delay(5000);
//       for (int i = 0; i < 150; i++)
//       {
//          analogWrite(10, i);
//          delay(2);
//       }
//    }
//    if (demo_mode)
//    {
//       delay(5000);
//       for (int i = 50; i > 0; i--)
//       {
//          analogWrite(11, i);
//          delay(20);
//       }
//    }
//    if (demo_mode)
//    {
//       delay(5000);
//       for (int i = 150; i > 0; i--)
//       {
//          analogWrite(9, i);
//          delay(2);
//       }
//    }
//    if (demo_mode)
//    {
//       delay(5000);

//       for (int i = 150; i > 0; i--)
//       {
//          analogWrite(10, i);
//          delay(2);
//       }
//    }
// }

void loop(void)
{
   timer.run();
   recvWithStartEndMarkers();
   if (newData == true)
   {
      strcpy(tempChars, receivedChars);
      parseData();
      newData = false;
      counter = 0;
      demo_mode = false;
   }else{
   
   
      analogWrite(9, _r);
      analogWrite(10, _g);
      analogWrite(11, _b);
   
   }
   
   //analogWrite(10, 23);
   //analogWrite(11, 255);
}