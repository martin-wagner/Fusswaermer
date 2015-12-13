
#include <xc.h>								// Processor definition file
#include <stdlib.h>								// standard library
#include "IO.h"
#include "globdef.h"
#include "temp_calc.h"

//parametrierung unter window - pic memory views - configuration bits
__CONFIG(FOSC_INTOSCIO & WDTE_ON & PWRTE_ON & MCLRE_ON & CP_OFF & CPD_OFF & BOREN_ON & IESO_OFF & FCMEN_ON);


volatile s16 given_value;
volatile s16 actual_value;

void init(void);

void main(void)
{
    u16 ad_result;
    s16 given_temp;
    s16 actual_temp;
    
    init();

    TMR0IE = 1;                         // enable timer interrupt
    ei();				// enable interrupts
    //main program loop
    while (1 == 1)
    {
        //watchdog reset
        CLRWDT();
        
        /* digitize and calculate given and actual value */
        AI_1_POLL_READ()
        ad_result = (u16)ADRESH << 8 | ADRESL;
        given_temp = get_temp(ad_result); //todo verwendet die kurve des NTC auf eingabe vom poti

        AI_0_POLL_READ()
        ad_result = (u16)ADRESH << 8 | ADRESL;
        actual_temp = get_temp(ad_result);

        if (actual_temp >= given_temp) {
            LED = 0;
        } else {
            LED = 1;
        }
        ENTER_CRITICAL();
        given_value = given_temp;
        actual_value = actual_temp;
        LEAVE_CRITICAL();
    }
}//main

/*
initialization process
*/
void init(void)
{
    /*
    Alignment of Bits: bit 7 ... bit 0
    */

    //OSCCON
    IRCF2 = 1; // -
    IRCF1 = 0; // -- 1 MHz
    IRCF0 = 0; // /
    OSTS = 0;  //use internal clock
    SCS = 1;   //use internal oscillator

    /* set up io ports */
    //switch all io to input
    TRISA = 0xff;
    TRISC = 0xff;

    //switch off all outputs
    PORTA = 0x00;
    PORTC = 0x00;
    //and now set i/os to output
    TRISA = 0b11011011;  // 1 = input

    /* set up adc */
    ANSEL = 0b00011000;		// select GPIO used as analogue input
    
    //ADCON0
    ADFM = 1;  //use 10 bit
    VCFG = 0;  //use vdd as ref
    ADON = 1;  //switch on converter

    //ADCON1
    ADCON1 = 0b00110000; //use dedicated internal oscillator for a/d

    /*set up timer interrupt */
    CLRWDT();
    OPTION_REG = 0b00000011; //must be set in one
    //T0CS = 0; //use internal clock for timer0
    //PSA = 0;  //use prescaler for timer0
    //PS2 = 0;
    //PS1 = 1;
    //PS0 = 1;  // Prescaler 1:16 -> 30,5 Hz at 1MHz

    //INTCON
    GIE =  0; //Disables all interrupts
    PEIE = 0; //Disables all peripheral interrupts
    T0IE = 0; //Disables the Timer0 interrupt

    //set watchdog prescaler to higher value
    WDTCON = 0b00010101;
    //            ---- prescaler 1:32768 -> ~1s at 32khz osc
}
