/*****************************************************************************
 * @Author                : Omar MEGAHED<omar.megahed@valeo.com>             *
 * @CreatedDate           : 2023-03-09 00:38:16                              *
 * @LastEditors           : Omar MEGAHED<omar.megahed@valeo.com>             *
 * @LastEditDate          : 2023-03-09 00:38:17                              *
 * @FilePath              : OS_priv.h                                        *
 ****************************************************************************/

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