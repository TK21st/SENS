/*
 * MMA.h
 *
 *  Created on: Oct 3, 2015
 *      Author: Tingkai
 */

#ifndef SOURCES_MMA_H_
#define SOURCES_MMA_H_






int8 MMA8451_Freedom_Init_50Hz(LDD_TDeviceData *DeviceDataPtr, struct AccelSensor *pthisAccel);
void MMA8451_Freedom_ReadData(LDD_TDeviceData *DeviceDataPtr, struct AccelSensor *pthisAccel);


#endif /* SOURCES_MMA_H_ */
