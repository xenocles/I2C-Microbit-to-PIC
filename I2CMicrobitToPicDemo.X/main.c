/*
 * File:   main.c
 * Author: Jonathan Carr
 *
 * Created on 28 December 2023, 11:26
 * 
 * This project is a demo/learning exercise to achieve two goals - [1] learn
 * how to program I2C on a PIC (I used 12LF1552 as I had one to hand and it
 * comes with MSSP/I2C) and [2] to set up the PIC as a slave to a Microbit.
 * 
 * The basic structure/principles can then be applied to build actual IC2 slave
 * devices in future, eg to make additional sensors and interesting GPIO 
 * modules for the Microbit.
 * 
 * The accompanying Makecode for the Microbit is included (makecode.js).
 * As is the circuitry for the PIC wiring up (TODO)
 * 
 * To use:
 *  - Use the left/right buttons on the Mibrobit to increment the number on
 *    the Microbit LED display.
 *  - Press the Microbit logo to send that number down the I2C bus. The LED
 *    attached to PIC.RA5 will flash that number of times.
 *  - Press the switch attached to PIC.RA4 multiple times, after a 0.5s 
 *    timeout that number is placed in the I2C buffer ready for the Microbit 
 *    to receive. 
 *  - The Microbit performs a read from the slave every second in a loop, if
 *    the returned number is greater than zero it is displayed on the Microbit
 *    LED display.
 */


#include <xc.h>
#include <builtins.h>

#include "init.h"
#include "util.h"

uint8_t dataIn = 0;             // Our buffer for any writes (master to slave)
uint8_t dataOut = 0;            // Our buffer for any reads (slave to master)
uint8_t buttonCount = 0;        // Counts how many times the button has been 
                                //    pressed within timerDuration
const int timerDuration = 500;
int timer = 500;                // The timeout before count is put into dataOut
                                //    in order that we can press the button 
                                //    multiple times before the data transmits

void __interrupt() ISR(void) {

    uint8_t buf;
    
    if (PIE1bits.SSP1IE && PIR1bits.SSP1IF) {   // I2C interrupt
        
        if (SSP1STATbits.R_nW) {        // Read operation
            SSP1BUF = dataOut;          // Send our buffered number to master
            dataOut = 0;                // Reset so we don't repeat ourselves
            SSP1CON1bits.CKP = 1;       // Release the clock stretch
        } else {                        // Write operation
            if (!SSP1STATbits.D_nA) {   // Address byte received
                buf = SSP1BUF;          // Clear BF via read of SSPBUF
                SSP1CON1bits.CKP = 1;   // Release the clock stretch
                
            } else {                    // Data byte received
                dataIn = SSP1BUF;          // Clear BF via read of SSPBUF
                SSP1CON1bits.CKP = 1;   // Release the clock stretch
            }
        }
    }

    if (PIR2bits.BCL1IF) {      // Bus collision interrupt
        buf = SSP1BUF;          // Clear BF
        PIR2bits.BCL1IF = 0;    // Clear BCLIF
        SSP1CON1bits.CKP = 1;   // Release the clock stretch
    }
    
    PIR1bits.SSP1IF = 0;        // Clear peripheral interrupt flag

    
    
    // RA4 IOC interrupt
    if (IOCAFbits.IOCAF4 == 1) {    // Button on RA4 pressed
        
        // Simple (ill advised?) debounce check, ensure switch is down for most
        // of 100ms. In testing this strikes a good balance between speed of 
        // acknowledgement and press/release false positives, for the button
        // and circuit I'm using anyway.
        // A better solution might be to check for 20ms continuous press maybe
        int downCount = 0;
        for (int i=0; i<50; i++) {
            __delay_ms(2);
            if (PORTAbits.RA4 == 1) {
                downCount++;
            }
        }
        if (downCount >= 25) {
            blink();                // Show switch was pressed
            buttonCount++;          // Increment our counter
            timer = timerDuration;  // Reset timeout counter
        }
        
        IOCAFbits.IOCAF4 = 0;       // Clear the interrupt flag
    }
}

void main(void) {
    initDevice();
    
    while(1) {
        
        if(dataIn > 0) {                // The Microbit has sent us a number
            blinkN(dataIn);
            dataIn=0;                   // Clear the number, wait for next number
        }
    
        if(buttonCount > 0) {           // We've captured some button presses on RA4
            if (timer-- <= 0) {
                dataOut = buttonCount;  // Put the count into the SPI send buffer
                
                buttonCount = 0;        // Reset everything
                timer = timerDuration;
            }
        }
    }
}
