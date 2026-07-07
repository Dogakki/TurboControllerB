/**
  ******************************************************************************
  * @file    app_tasks.h
  * @brief   Task entry function declarations
  ******************************************************************************
  */
#ifndef __APP_TASKS_H__
#define __APP_TASKS_H__

void Task_Safety(void *arg);
void Task_Control(void *arg);
void Task_Motor(void *arg);
void Task_Comm(void *arg);
void Task_Sensor(void *arg);
void Task_Storage(void *arg);
void Task_Debug(void *arg);
void Task_Led(void *arg);

#endif /* __APP_TASKS_H__ */
