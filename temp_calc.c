#include "globdef.h"
#include "temp_calc.h"
#include "float.h"

/* factors for ax2 + bx + c */
#define A 0.000069930561
#define B -0.17929916
#define C 97.982055

/* Lookup Table 0..1024 -> Temperatur
 * For thermistor NTC 10k 103AT */
u16 get_temp(u16 digi_value)
{
    float input;
    s16 result;

    input = (float)digi_value;
    result = (s16) (A * (input * input) + B * input + C);

    if (result < 0) {
        return 0;
    } else if (result > 100) {
        return 100; //formula only valid from 0 .. 100
    }
    return (u16)result;

//
//    switch (digi_value) {
//        case 236 ... 242:
//            return 60;
//        case 243 ... 248:
//            return 59;
//        case 249 ... 255:
//            return 58;
//        case 256 ... 261:
//            return 57;
//        case 262 ... 268:
//            return 56;
//        case 269 ... 274:
//            return 55;
//        case 275 ... 281:
//            return 54;
//        case 282 ... 287:
//            return 53;
//        case 288 ... 294:
//            return 52;
//        case 295 ... 301:
//            return 51;
//        case 302 ... 307:
//            return 50;
//        case 308 ... 314:
//            return 49;
//        case 315 ... 321:
//            return 48;
//        case 322 ... 329:
//            return 47;
//        case 330 ... 336:
//            return 46;
//        case 337 ... 343:
//            return 45;
//        case 344 ... 351:
//            return 44;
//        case 352 ... 359:
//            return 43;
//        case 360 ... 367:
//            return 42;
//        case 368 ... 375:
//            return 41;
//        case 376 ... 383:
//            return 40;
//        case 384 ... 391:
//            return 39;
//        case 392 ... 400:
//            return 38;
//        case 401 ... 408:
//            return 37;
//        case 409 ... 417:
//            return 36;
//        case 418 ...426:
//            return 35;
//        case 427 ... 435:
//            return 34;
//        case 436 ... 444:
//            return 33;
//        case 445 ... 454:
//            return 32;
//        case 455 ... 463:
//            return 31;
//        case 464 ... 473:
//            return 30;
//        case 474 ... 483:
//            return 29;
//        case 484 ... 492:
//            return 28;
//        case 493 ... 501:
//            return 27;
//        case 502 ... 511:
//            return 26;
//        case 512 ... 521:
//            return 25;
//        case 522 ... 530:
//            return 24;
//        case 531 ... 540:
//            return 23;
//        case 541 ... 550:
//            return 22;
//        case 551 ... 560:
//            return 21;
//        case 561 ... 570:
//            return 20;
//        case 571 ... 700:
//            return 19;
//
//        default:
//            /* unknown */
//            return 100;

            //die lookuptable belegt 40% des programmspeichers???
//    }
}


