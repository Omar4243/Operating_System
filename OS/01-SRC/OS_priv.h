/**
 * @ Author: Omar Megahed
 * @ Create Time: 2023-03-07 00:34:59
 * @ Modified by: Omar Megahed
 * @ Modified time: 2023-03-08 23:24:59
 * @ Description:
 */
#ifndef _OS_PRIV_H_
#define _OS_PRIV_H_
#include "std_type.h"
/*task type*/
typedef struct 
{
 void (*Func)(void);
 u8  Period_Ticks;
 u8  Delay_Ticks ;
 u8  RunMe;
}OsTask_t;

/*system tick count*/
typedef u8 SysTick_t;

#endif