/*
 * TCS_RGB.h
 *
 *  Created on: Sep 28, 2015
 *      Author: Tingkai
 */

#ifndef SOURCES_TCS_RGB_H_
#define SOURCES_TCS_RGB_H_


//function prototypes

uint8_t RGB_Read8(LDD_TDeviceData *DeviceDataPtr, uint8_t REG);
void RGB_Write8(LDD_TDeviceData *DeviceDataPtr, uint8_t REG, uint8_t value);
void RGB_Enable(void);
void RGB_Disable(void);
void RGB_Init(void);
uint16_t RGB_Read16(LDD_TDeviceData *DeviceDataPtr, uint8_t REG);

#endif /* SOURCES_TCS_RGB_H_ */
