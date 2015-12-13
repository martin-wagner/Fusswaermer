#include <htc.h>								// Processor definition file
#include "IO.h"
#include "globdef.h"
#include "pid.h"

extern volatile s16 given_value;
extern volatile s16 actual_value;

void interrupt isr(void)
{
    static u8 postscaler;
    static u8 control_value;
    static u8 cycle;    
    static u8 pwm_value = 100; //start full power

    if (TMR0IE && TMR0IF) {
        if (postscaler >= 5) {

            control_value = pi(given_value, actual_value);

            /* make slow pwm signal out of control 0..100% */
            if (cycle < pwm_value) {
                HEATER = 1;
                cycle ++;
            } else if (cycle >= 100) {  //one pulse is 10s
                cycle = 0;
                pwm_value = control_value;
            } else {
                HEATER = 0;
                cycle ++;
            }

//            if (actual_value < given_value) {
//                HEATER = 1;
//            } else {
//                HEATER = 0;
//            }

            postscaler = 0;
        } else {
            postscaler ++;
        }
    }
    TMR0IF = 0;
    INTF = 0;
    ei();
}
