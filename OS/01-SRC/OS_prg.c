/*****************************************************************************
 * @Author                : Omar MEGAHED<omar.megahed@valeo.com>             *
 * @CreatedDate           : 2023-03-09 00:37:06                              *
 * @LastEditors           : Omar MEGAHED<omar.megahed@valeo.com>             *
 * @LastEditDate          : 2023-03-09 00:37:10                              *
 * @FilePath              : OS_prg.c                                         *
 ****************************************************************************/


#include "OS_int.h"
#include "OS_cfg.h"
#include "bit_math.h"
#include "std_type.h"
#include "SysTick.h" //TODO:use wraper to systick update

static OsTask_t TasksDefinitions[MAX_TASKS_NUM];
/****************************************************************************
*                        Scheduler initialize                               *
*****************************************************************************/
void SCH_Init(u8 TickTime)//tick time in ms
{
    u8 i=(u8)0;
    for (i = (u8)0; i < MAX_TASKS_NUM; i++)
    {
      TasksDefinitions[i].Func = STD_NULL;
      TasksDefinitions[i].RunMe=0;
    }
  // Timer Tick (ms) configuration
	SysTick_Interrupt_Init(TickTime); //TODO:use wraper to set callback
}
/****************************************************************************
*                        Scheduler start                                    *
*****************************************************************************/
void SCH_Start(void)
{
  // Enable timer To start
	 SysTick_Start();  //TODO:use wraper to enable systick timer 
}
/****************************************************************************
*                        Scheduler Add Task                                 *
*****************************************************************************/
void SCH_AddTask(void (*Func)(void), SysTick_t Delay, SysTick_t Period, u8 Priority)
{
 
   if (Priority < MAX_TASKS_NUM)
      {
          if (Func != STD_NULL)
             {
               TasksDefinitions[Priority].Func = Func;
               TasksDefinitions[Priority].Delay_Ticks = Delay;
               TasksDefinitions[Priority].Period_Ticks = Period;
               TasksDefinitions[Priority].RunMe=0;
             }
           else
           { 
             /*ERROR PRIORTY*/
           }
     }
    else
    { 
      /*NO EMPTY LOCATION*/
    }
  }
/****************************************************************************
*                        Scheduler Delete Task                              *
*****************************************************************************/
void SCH_DelTask(void (*Func)(void))
{
  u8 i = (u8)0;
  //search for task name 
  for (i = (u8)0; i < MAX_TASKS_NUM; i++)
  {
      if (TasksDefinitions[i].Func == Func)
         {
           //clear Task Function 
           TasksDefinitions[i].Func = STD_NULL;
           break;
         }
  }
}
/****************************************************************************
*                        Scheduler Update  (ISR)                             *
*****************************************************************************/
void SCH_Update(void)
{
  u8 i = (u8)0;
  for (i = (u8)0; i < MAX_TASKS_NUM; i++) // loop for all tasks
  {  
      if (TasksDefinitions[i].Func != STD_NULL) // check task function is located or deleted
      {
          if (TasksDefinitions[i].Delay_Ticks > (u8)0) // check task delay time 
          {
            TasksDefinitions[i].Delay_Ticks--;
          }
          else if (TasksDefinitions[i].Delay_Ticks == (u8)0) // check task delay time 
          {
              TasksDefinitions[i].RunMe ++;// task is ready to execute
              if (TasksDefinitions[i].Period_Ticks > (u8)0) // task periodicity check
              {
                TasksDefinitions[i].Delay_Ticks = TasksDefinitions[i].Period_Ticks-((u8)1); // task will be ready again after period
              }
              else
              {
                /* one shot task*/
              }
          }
          else
          {
            /*ERORR*/
          }
      }
      else
      {
        /*Task deleted*/
      }
  }  
}  
/****************************************************************************
*                           Scheduler Dispatch                              *
*****************************************************************************/
void SCH_Dispatch(void)
{
  u8 i = (u8)0;
  for (i = (u8)0; i < MAX_TASKS_NUM; i++)
  {
      if ((TasksDefinitions[i].Func != STD_NULL) && (TasksDefinitions[i].RunMe > (u8)0))
      {
		  	  (*TasksDefinitions[i].Func)();//Execute task function
          TasksDefinitions[i].RunMe --;//task status blocked
          if (TasksDefinitions[i].Period_Ticks == (u8)0)//one shot task "execute once then deleted"
          {
            SCH_DelTask(TasksDefinitions[i].Func);//delete one shot task
          }  
      }
  }  
}
