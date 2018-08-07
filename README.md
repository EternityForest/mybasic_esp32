# MY-BASIC for Arduino ESP32

There's plenty of interpreted languages on the ESP, but I wanted one that could easily be packaged as an arduino library.

All credit to the actual interpreter goes to https://github.com/paladin-t/my_basic, I just packaged is as a library and wrote a few
API bindings.


This is not a stable API at the moment. The bindings to control the hardware are nowhere near complete.

But you can compile a basic interpreter, type a program in and run it by sending a new line beginning with -, all from the Arduino IDE!

This entire repo is an Arduino lib, just upload the example sketch and try it out!


## API

You are free to use my-basic's native API, but the library provides a wrapper layer that can manage multiple running
program in separate "threads". These are real freeRTOS threads, but use a global interpreter lock.

The library provides a singleton class MyBasic with the following methods:



### begin(char threads)
Start the my-basic system with the given number of threads, up to a maxium of 8. Each will have MyBasic.stackSize bytes of stack, defaulting to 2048. These are python-style threads that use a global interpreter lock, switching every 200 instructions.


### mb_interpreter_t * rootInterpreter
This is the root interpreter, where you probably want to add any extra functions.

### lock()/unlock()
Get or release the global interpreter lock. You need to get the lock before you can do anythong with the root interpreter(or any interpreter)

### loadProgram(const char * code, const char * id)
Load a program, giving it the ID. If a program already exists with that ID, then close it. The new program will be child
or the root interpreter, and will have access to anything in the parent scope, but can't modify them without the export(var) function.

If the current loaded program with that ID has the same first 30 bytes, do nothing.

If the program is busy, it will wait a bit for it to stop, but eventually close it, so don't replace busy programs
if they need a clean shutdown.

### updateProgram(const char * code, const char * id)
Similar to loadProgram, but if the program is already loaded, it will replace the code without changing variables.

You can use this to implement pseudo-REPLs.

### runLoaded(const char * id)

Run the current loaded program in a background thread. 


### closeProgram(const char * id)
Wait a bit for the program to stop whatever it is doing, stop it, then unload it.




## My-basic modifications

I've added the function mb_reset_preserve, which is just like mb_reset but doesn't clear variables, that's how
we can do a real REPL. We also have mb_set_yield, which allows you pass in a yield function called every 100 instructions. This library
uses it to release the GIL, wait 2 freeRTOS ticks, and re-acquire it.

Because of the way I handle memory allocation, the interpreter contexts now have shared state that means you can't access my-basic in different threads without a lock.

