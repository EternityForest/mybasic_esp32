/*
** Copyright (C) 2018 Daniel Dunn
**
** Permission is hereby granted, free of charge, to any person obtaining a copy of
** this software and associated documentation files (the "Software"), to deal in
** the Software without restriction, including without limitation the rights to
** use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
** the Software, and to permit persons to whom the Software is furnished to do so,
** subject to the following conditions:
**
** The above copyright notice and this permission notice shall be included in all
** copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
** IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
** FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
** COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
** IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
** CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "bas_arduino.h"

/*BASIC terminal example
   Type your commands with only newline line endings.
   Then type a - at the start of a new line to reset everything and run the program.

   Whenever you run the program, anything you type after that is part of a completely new program.

   You have access to some functions that pretty much pass through straight through to the arduino functions(The constants like HIGH are not available though)

   analogRead(pin)
   pinMode(pin,mode)
   digitalWrite(pin, value)
   millis()

   You also have access to some extra function for dealing with binary arrays. There's a bit of overhead, but these use real malloc()ed memory,
   so you can store thousands of bytes this way.:

   malloc(len): returns a bytearray object, it should be garbage collected so you don't have to free it
   peek(bytearray, index): look at a byte in a bytearray
   poke(bytearray, index, value): write a byte into a bytearray


   sersend(port, bytearray, len): Send a bytearray out a serial port.
   serbegin(port, baud): Set up one of the Arduino serial port objects

*/
char bas_prg[10000];
int bas_prgp = 0;


//An event has an event type code, and some data. It says "This interpreter asked to handle this event", so pass this data to their handler in the eventhandlers dict they have.
//To tell the sender to stop it, we must
struct mb_event_t
{
  uint32_t type;
  void * data;
  mb_interpreter_t * interpreter;
};



void setup() {
  char * fooID = "foo";
  MyBasic.begin(3);
  Serial.begin(115200);


  //Load an empty program
  MyBasic.loadProgram("", "SerialPortRepl");
  Serial.println("Interpreter loaded. Type a program followed by - on its own line to run");
  while (1)
  {

    if (Serial.available())
    {
      bas_prg[bas_prgp] = Serial.read();
      //Echo
      Serial.write(bas_prg[bas_prgp]);
      bas_prg[bas_prgp + 1] = 0;


      if (bas_prg[bas_prgp] == '-')
      {
        if (bas_prg[bas_prgp - 1] == '\n')
        {
          Serial.println("Running Program!");
          bas_prg[bas_prgp] = 0;
          bas_prgp = -1;
          //Load the program
          MyBasic.updateProgram(bas_prg, "SerialPortRepl");
          
          MyBasic.runLoaded("SerialPortRepl");
        }
      }

      bas_prgp += 1;
    }
  }

}
void loop() {
  // put your  main code here, to run repeatedly:

}