/*
 * app_scheduler.h
 *
 *  Created on: Nov 27, 2023
 *      Author: Windows
 */

#ifndef APP_SCHEDULER_H_
#define APP_SCHEDULER_H_

#include "stdint.h"

#define SCH_MAX_TASKS 			10
#define	NO_TASK_ID				0
#define TICK					10

typedef struct {
	void ( * pTask)(void);
	uint32_t Delay;
	uint32_t Period;
	uint8_t RunMe;
	uint32_t TaskID;
} sTask;

void SCH_Init(void);
void SCH_Update(void);
void SCH_Add_Task(void (*p_function)(), uint32_t DELAY, uint32_t PERIOD);
void SCH_Dispatch_Tasks(void);
uint8_t SCH_Delete_Task(uint32_t TASK_ID);
#endif /* APP_SCHEDULER_H_ */
