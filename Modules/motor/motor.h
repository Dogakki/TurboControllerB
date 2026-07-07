/**
  ******************************************************************************
  * @file    motor.h
  * @brief   Motor/pump control module
  ******************************************************************************
  */
#ifndef __MOTOR_H__
#define __MOTOR_H__

#include <stdint.h>
#include <stdbool.h>

void motor_init(void);
void motor_start(void);
void motor_stop(void);
void motor_set_duty(uint8_t percent);
uint8_t motor_get_duty(void);
bool motor_is_running(void);

#endif /* __MOTOR_H__ */
