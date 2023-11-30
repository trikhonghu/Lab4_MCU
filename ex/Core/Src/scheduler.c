/*
 * app_scheduler.c
 *
 *  Created on: Nov 27, 2023
 *      Author: Windows
 */

#include "scheduler.h"
// The array of tasks
static sTask SCH_tasks_G[SCH_MAX_TASKS];

void SCH_Init(void){
	for(int i = 0; i < SCH_MAX_TASKS; i++){
		SCH_tasks_G[i].pTask = 0x0000000;
		SCH_tasks_G[i].Delay = 0;
		SCH_tasks_G[i].Period = 0;
		SCH_tasks_G[i].RunMe = 0;
		SCH_tasks_G[i].TaskID = 0;
	}
}

void SCH_Update(void){
	 for(int i = 0; i < SCH_MAX_TASKS; i++){
		 if(SCH_tasks_G[i].Delay > 0){
			 SCH_tasks_G[i].Delay --;
		 }else{
			 SCH_tasks_G[i].Delay = SCH_tasks_G[i].Period;
			 SCH_tasks_G[i].RunMe += 1;
		 }
	 }
}

void SCH_Add_Task(void (* pFunction)(), uint32_t DELAY, uint32_t PERIOD){
//	if(current_index_task < SCH_MAX_TASKS){
//
//		SCH_tasks_G[current_index_task].pTask = pFunction;
//		SCH_tasks_G[current_index_task].Delay = DELAY;
//		SCH_tasks_G[current_index_task].Period = PERIOD;
//		SCH_tasks_G[current_index_task].RunMe = 0;
//		SCH_tasks_G[current_index_task].TaskID = current_index_task;
//
//		current_index_task ++;
//	}
	uint8_t Index = 0;
	while ((SCH_tasks_G[Index].pTask != 0) && (Index < SCH_MAX_TASKS)) {
		Index++;
	}
	SCH_tasks_G[Index].pTask = pFunction;
	SCH_tasks_G[Index].Delay = DELAY/TICK;
	SCH_tasks_G[Index].Period = PERIOD/TICK;
	SCH_tasks_G[Index].RunMe = 0;
	SCH_tasks_G[Index].TaskID = Index;

}


void SCH_Delete_Task(uint32_t taskID){
	uint8_t j;
	SCH_tasks_G[taskID].pTask = 0;
	SCH_tasks_G[taskID].Period = 0;
	SCH_tasks_G[taskID].Delay = 0;
	SCH_tasks_G[taskID].RunMe = 0;
	SCH_tasks_G[taskID].TaskID = 0;

	for( j = taskID; j < SCH_MAX_TASKS - 1; j++){
		SCH_tasks_G[j].pTask = SCH_tasks_G[j+1].pTask;
		SCH_tasks_G[j].Period = SCH_tasks_G[j+1].Period;
		SCH_tasks_G[j].Delay = SCH_tasks_G[j+1].Delay;
		SCH_tasks_G[j].RunMe = SCH_tasks_G[j+1].RunMe;
		SCH_tasks_G[j].TaskID = SCH_tasks_G[j+1].TaskID;
	}
}

void SCH_Dispatch_Tasks(void){
	 for(int i = 0; i < SCH_MAX_TASKS; i++){
		 if(SCH_tasks_G[i].RunMe > 0){
			 SCH_tasks_G[i].RunMe --;
			 if(SCH_tasks_G[i].pTask){
				 (*SCH_tasks_G[i].pTask)();
			 }
			 if(!SCH_tasks_G[i].Period){
				 SCH_Delete_Task(i);
			 }
		 }
	 }
}
