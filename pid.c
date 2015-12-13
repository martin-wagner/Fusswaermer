
#include <xc.h>								// Processor definition file
#include <stdlib.h>								// standard library
#include "IO.h"
#include "globdef.h"
#include "temp_calc.h"
#include "pid.h"

/* defines to pid control */
#define DT 0.1 //s
//#define KP 2.975
//#define KI 0.0053894928 calculated values
#define KP 4.0
#define KI 0.007



static float integral_value = 0;

/* calculates control value in 0..100% */
u8 pi(s16 given, s16 actual)
{
    s16 error;
    s16 result;

    error = given - actual;

    integral_value = integral_value + (float)error * DT;
    if (integral_value > (100 / KI)) {
        integral_value = (100 / KI); //limits integral value to 100% overall
    }

    /* addition of P and I part */
    result = (s16)(KP * (float)error + KI * integral_value);

    if (result < 0) {
        result = 0;
    } else if (result > 100) {
        result = 100;
    }
    return result;
}