/* 
 * File:   util.c
 * Author: Jonathan Carr
 *
 * Created on 28 December 2023, 11:47
 */

#include "util.h"

#include <xc.h>
#include <builtins.h>

#include "init.h"   // Builtins.h needs _XTAL_FREQ to calc correct timings

void blinkN(int times) {
    for(int i = 0; i < times; i++) {
    LATAbits.LATA5 = 1;
    __delay_ms(75);
    LATAbits.LATA5 = 0;
    __delay_ms(75);
    }
}

void blink(void) {
    LATAbits.LATA5 = 1;
    __delay_ms(50);
    LATAbits.LATA5 = 0;
}
