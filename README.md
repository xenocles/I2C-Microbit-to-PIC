# I2C-Microbit-to-PIC

This project is a basic demo/learning exercise to achieve two goals - 

1. Program a PIC to act as an I2C slave
1. Connect this to a Microbit and demo two-way communication

To keep things simple this project just flashes an LED to demonstrate
master-to-slave (write), and relays a count of button pushes back to 
the Microbit to demonstrate slave-to-master (read). However the basic 
structure/principles can be applied to more complex IC2 slaves, eg to
make additional sensors and interesting GPIO modules for the Microbit.

## Repository contents

1. An MPLAB X project with the PIC code in C (using xc8 compiler)
1. Makecode Javascript for the Microbit to talk to the PIC (see usage instructions below)
1. An Eeschema schematic explaining the wiring needed between the PIC and Microbit

## Building

The schematic includes ICSP breakout and assumes use of a PIC12LF1552 (this
is basically what I had on hand at the time). If you wish to use a different 
PIC you will need to check the PIC datasheet and align the project settings 
and code accordingly:

1. PIC12LF1552 is a 3.3v device, if you're using a 5v device you may need to consider power requirements (the Microbit can only source 3v)
1. PIC12LF1552 is a small 8-pin package, I've used the pins as follows:
   - RA0/Pin 7: ICSP DAT
   - RA1/Pin 6: ICSP CLK and I2C SCL
   - RA2/Pin 5: I2C SDA
   - RA3/Pin 4: ICSP MCLR
   - RA4/Pin 3: Push button input
   - RA5/Pin 2: LED output
1. `init.c` sets up all the required registers for the above GPIO, I2C and associated interrupts
1. `main.c` checks and resets interrupt flags and I2C buffers - these may be different for your device

Note the I2C address for the PIC (slave) is '24'. In the code this appears as `SSP1ADD = 0x30;` because 
the PIC requires this to be configured with the full 8 bits that will appear in the I2C address byte.
In other words the address needs to be shifted one bit to the left to leave the LSB empty for the 
eighth R/W control bit.

It is fine to source the PIC's power from the Microbit; see the schematic. Just make sure you
disconnect the Microbit SCL line before using your PIC programmer (if using ICSP), or disconnect
the Microbit entirely and power the circuit from your programmer during programming.

## How to use

1. Use the left/right buttons on the Mibrobit to increment the number on the Microbit LED display.
1. Press the Microbit logo to send that number down the I2C bus. The LED attached to the PIC will flash that number of times.
1. Press the button attached to PIC.RA4 multiple times, after a 0.5s timeout (to capture sequential presses) that number is placed in the I2C buffer ready for the Microbit to receive. 
1. The Microbit performs a read from the slave every second in a loop, if the returned number is greater than zero it is displayed on the Microbit LED display.

## Version info

- MPLAB X v6.15
- xc8-cc v2.45 (C99)
- Eeschema v5.1.9 (Debian 11/Bullseye)