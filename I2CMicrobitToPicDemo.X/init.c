/*
 * File:   init.c
 * Author: Jonathan Carr
 *
 * Created on 28 December 2023, 11:28
 */

#include "init.h"

#include <xc.h>

/*
 * Private function declarations
 */
void initI2C(void);
void initInterrupts(void);

/*
 * Public functions
 */
void initDevice(void) {
    TRISAbits.TRISA4 = 1;   // Set RA4 to INPUT for external button
    ANSELAbits.ANSA4 = 0;   // Ensure RA4 is in digital mode, not analogue
    
    TRISAbits.TRISA5 = 0;   // Set RA5 to OUTPUT to drive LED
    LATAbits.LATA5 = 0;     // Start with LED off
    
    initI2C();
    initInterrupts();
}

/*
 * Private functions
 */
void initI2C(void) {
    TRISAbits.TRISA0 = 1;       // Set RA0 (SDO) as input
    TRISAbits.TRISA1 = 1;       // Set RA1 (SCK) as input
    ANSELAbits.ANSA0 = 0;
    ANSELAbits.ANSA1 = 0;
    
    SSP1ADD = 0x30;             // I2C slave address = (0x30 >> 1) = 24
                                // The PIC requires the SSP1ADD to be shifted
                                // one bit to the left to allow for R/W LSB
                                // in the I2C address byte
    
    SSP1STATbits.SMP = 1;       // SMP Slew rate control disabled for Standard Speed mode
                    
    SSP1CON1bits.SSPM = 0b0110; // SSPM<3:0> I2C slave mode, 7-bit addressing
    SSP1CON1bits.SSPEN = 1;     // SSPEN sync serial port enable - enabled
    
    SSP1CON2bits.SEN = 1;       // SEN start condition stretch enable - enabled
    
//    SSP1CON3bits.PCIE = 1;      // PCIE stop condition int enable - enabled
    SSP1CON3bits.SBCDE = 1;     // SBCDE slave mode bus collision int enable - disabled
    
}

void initInterrupts(void) {
    IOCAPbits.IOCAP4 = 1;   // Enable positive edge IOC on RA4
    IOCAFbits.IOCAF4 = 0;   // Clear interrupt flag for RA4 IOC
   
    INTCONbits.IOCIE = 1;   // Enable interrupt-on-change
                            // The similar IOCIF flag in the INTCON reg is read
                            // only, cleared when IOC flags in IOCBF reg have
                            // been cleared by software
     
    PIR1bits.SSP1IF = 0;    // Clear MSSP interrupt flag
    PIR2bits.BCL1IF = 0;    // Clear collision interrupt flag
    PIE1bits.SSP1IE = 1;    // Enable MSSP peripheral interrupts
    PIE2bits.BCL1IE = 1;    // Enable MSSP bus collision interrupts
    
    INTCONbits.PEIE = 1;    // Turn on peripheral interrupts
    INTCONbits.GIE = 1;     // Turn on interrupts
}