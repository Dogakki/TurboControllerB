/**
  ******************************************************************************
  * @file    sub_enable.h
  * @brief   SUB_EN monitoring and global enable/disable
  ******************************************************************************
  */
#ifndef __SUB_ENABLE_H__
#define __SUB_ENABLE_H__

#include <stdbool.h>

void sub_enable_init(void);
bool sub_enable_is_active(void);
void sub_enable_check_and_protect(void);

#endif /* __SUB_ENABLE_H__ */
