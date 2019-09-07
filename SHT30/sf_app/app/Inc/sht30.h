#ifndef __SHT30_H
#define __SHT30_H

#include "stm32f1xx_hal.h"

#define SHT31_DEFAULT_ADDR 0x44 /**< SHT31 Default Address */
#define SHT31_MEAS_HIGHREP_STRETCH                                             \
  0x2C06 /**< Measurement High Repeatability with Clock Stretch Enabled */
#define SHT31_MEAS_MEDREP_STRETCH                                              \
  0x2C0D /**< Measurement Medium Repeatability with Clock Stretch Enabled */
#define SHT31_MEAS_LOWREP_STRETCH                                              \
  0x2C10 /**< Measurement Low Repeatability with Clock Stretch Enabled*/
#define SHT31_MEAS_HIGHREP                                                     \
  0x2400 /**< Measurement High Repeatability with Clock Stretch Disabled */
#define SHT31_MEAS_MEDREP                                                      \
  0x240B /**< Measurement Medium Repeatability with Clock Stretch Disabled */
#define SHT31_MEAS_LOWREP                                                      \
  0x2416 /**< Measurement Low Repeatability with Clock Stretch Disabled */
#define SHT31_READSTATUS 0xF32D  /**< Read Out of Status Register */
#define SHT31_CLEARSTATUS 0x3041 /**< Clear Status */
#define SHT31_SOFTRESET 0x30A2   /**< Soft Reset */
#define SHT31_HEATEREN 0x306D    /**< Heater Enable */
#define SHT31_HEATERDIS 0x3066   /**< Heater Disable */


void SHT_Init(void);
int sht30_data_process(void);
int sht30_crc8_check(uint8_t *p,uint8_t num_of_data,uint8_t CrcData);
#endif
