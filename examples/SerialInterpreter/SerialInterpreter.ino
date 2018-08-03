#include "bas_arduino.h"


/*BASIC terminal example
   Type your commands with only newline line endings.
   Then type a - at the start of a new line to reset everything and run the program.

   Whenever you run the program, anything you type after that is part of a completely new program, but the state(variables, functions)
   stays.

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


void setup() {
  Serial.begin(115200);
  struct mb_interpreter_t* bas = NULL;
  mb_init();
  mb_open(&bas);





  enableArduinoBindings(bas);


  while (1)
  {

    if (Serial.available())
    {
      bas_prg[bas_prgp] = Serial.read();
      Serial.write(bas_prg[bas_prgp]);
      bas_prg[bas_prgp + 1] = 0;


      if (bas_prg[bas_prgp] == '-')
      {
        if (bas_prg[bas_prgp - 1] == '\n')
        {
          Serial.println("Running Program!");
          bas_prg[bas_prgp] = 0;
          bas_prgp = -1;
          mb_load_string(bas, bas_prg, true);
          mb_run(bas, true);
          mb_reset_preserve(&bas, 0);
        }
      }

      bas_prgp += 1;


    }


  }

}
void loop() {
  // put your  main code here, to run repeatedly:

}
