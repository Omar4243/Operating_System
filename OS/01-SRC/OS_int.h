#ifndef OS_H
#define OS_H
/*Headers*/
#include "std_type.h"

/*Function Prototype*/
/**
 * @brief schadular initialize (Tick Time in ms) 
 * 
 * @param TickTime 
 */
void SCH_Init(u8 TickTime);
/**
 * @brief schadular update
 * 
 */
void SCH_Update(void);
/**
 * @brief Dispatcher 
 * 
 */
void SCH_Dispatch(void);
/**
 * @brief 
 * 
 * @param Func :pointer to task function
 * @param Delay : no of systick delay
 * @param Period :periodicity of task
 * @param priority :priority of task
 */
void SCH_AddTask(void(*Func)(void),SysTick_t Delay,SysTick_t Period,u8 priority);
/**
 * @brief delet task
 * 
 * @param Func pointer to task function
 */
void SCH_DelTask(void(*Func)(void));
/**
 * @brief schadular start
 * 
 */
void SCH_Start(void);
#endif
