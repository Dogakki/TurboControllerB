/**
  ******************************************************************************
  * @file    fault_config.h
  * @brief   Fault thresholds, timeout values, and fault ID definitions
  ******************************************************************************
  */
#ifndef __FAULT_CONFIG_H__
#define __FAULT_CONFIG_H__

/* ---- Fault IDs (bitmask) ---- */
#define FAULT_ID_NONE               0x0000
#define FAULT_ID_SUB_DISABLED       (1U << 0)
#define FAULT_ID_ESC                (1U << 1)
#define FAULT_ID_GLOW_OVERCURRENT   (1U << 2)
#define FAULT_ID_THERMOCOUPLE_OPEN  (1U << 3)
#define FAULT_ID_OVERTEMP           (1U << 4)
#define FAULT_ID_SPEED_LOST         (1U << 5)
#define FAULT_ID_CAN_TIMEOUT        (1U << 6)
#define FAULT_ID_ADC_ABNORMAL       (1U << 7)

/* ---- Thresholds ---- */
#define GLOW_OVERCURRENT_MA         10000   /* mA */
#define OVERTEMP_LIMIT_C            800.0f  /* degrees C */
#define SPEED_LOST_TIMEOUT_MS       500     /* ms without capture = lost */
#define CAN_RX_TIMEOUT_MS           1000    /* ms without CAN RX = timeout */
#define PREHEAT_TIMEOUT_MS          30000   /* 30s max preheat */

/* ---- INA199 Current Sense ---- */
#define INA199_RSHUNT_OHM           0.005f
#define INA199_GAIN                 50.0f
#define INA199_VREF                 3.3f

#endif /* __FAULT_CONFIG_H__ */
