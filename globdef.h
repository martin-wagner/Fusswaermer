/* 
 * File:   globdef.h
 * Author: martin
 *
 * Created on November 17, 2013, 9:45 AM
 */

#ifndef GLOBDEF_H
#define	GLOBDEF_H

#ifdef	__cplusplus
extern "C" {
#endif

/* Microchip xc8 */
#define u8 unsigned char
#define u16 unsigned int
#define u24 unsigned short long
#define u32 unsigned long

#define s8 signed char
#define s16 int
#define s24 signed short long
#define s32 signed long long

#define ENTER_CRITICAL() di()
#define LEAVE_CRITICAL() ei()









#ifdef	__cplusplus
}
#endif

#endif	/* GLOBDEF_H */

