# MY-BASIC for Arduino ESP32

There's plenty of interpreted languages on the ESP, but I wanted one that could easily be packaged as an arduino library.

All credit to the actual interpreter goes to https://github.com/paladin-t/my_basic, I just packaged is as a library and wrote a few
API bindings.


This is not a stable API at the moment. The bindings to control the hardware are nowhere near complete. I may even want to add a nice C++
OOP wrapper around things(but this is fine for now, my-basic has a pretty good API).

But you can compile a basic interpreter, type a program in and run it by sending a new line beginning with -, all from the Arduino IDE!

This entire repo is an Arduino lib, just upload the example sketch and try it out!
