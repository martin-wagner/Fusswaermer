#ifndef IO_H
#define IO_H

#define HEATER RA2
#define LED RA5

#define AI_0 RC0
#define AI_0_SELECT() (ADCON0bits.CHS = 0b100)
#define AI_1 RC1
#define AI_1_SELECT() (ADCON0bits.CHS = 0b101)
#define AI_START() (GO_nDONE = 1)
#define AI_POLL() while (GO_nDONE == 1){}
#define AI_0_POLL_READ() {AI_0_SELECT(); AI_START(); AI_POLL();}
#define AI_1_POLL_READ() {AI_1_SELECT(); AI_START(); AI_POLL();}

#endif