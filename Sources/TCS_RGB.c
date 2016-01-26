/*
 * TCS_RGB.c
 *
 *  Created on: Sep 28, 2015
 *      Author: Tingkai
 */
#include "Events.h"
#include "RGB_Sensor.h"
#include "string.h"

#include "build.h"
#include "TCS_RGB.h"


uint8_t I2C_Buf[I2C_BUF_LEN];




// read MMA8451 accelerometer data on Freedom board data over I2C
uint8_t RGB_Read8(LDD_TDeviceData *DeviceDataPtr, uint8_t REG){
	uint8_t y;
	LDD_I2C_TBusState BusState;		// I2C bus state

	// set up the RGB address
	RGB_Sensor_SelectSlaveDevice(DeviceDataPtr, LDD_I2C_ADDRTYPE_7BITS, RGB_ADDR);
	// set up the address of the first output register
	I2C_Buf[0] = (RGB_COMMAND_BIT | REG);
	RGB_I2C_SENT_FLAG = FALSE;
	RGB_Sensor_MasterSendBlock(DeviceDataPtr, I2C_Buf, 1, LDD_I2C_NO_SEND_STOP);
	// wait until the I2C sent callback function sets the sent flag
	while (!RGB_I2C_SENT_FLAG);

	// read the 6 bytes of sequential sensor data
	RGB_I2C_RCVD_FLAG = FALSE;
	RGB_Sensor_MasterReceiveBlock(DeviceDataPtr, I2C_Buf, 1, LDD_I2C_SEND_STOP);
	// wait until the I2C received callback function sets the received flag
	while (!RGB_I2C_RCVD_FLAG);
	// wait until the I2C bus is idle

	do
	{
		RGB_Sensor_CheckBus(DeviceDataPtr, &BusState);
	} while (BusState != LDD_I2C_IDLE);
	y = I2C_Buf[0];
	return y;
}

void RGB_Write8(LDD_TDeviceData *DeviceDataPtr, uint8_t REG, uint8_t value){
	LDD_I2C_TBusState BusState;		// I2C bus state

	// set up the RGB address
	RGB_Sensor_SelectSlaveDevice(DeviceDataPtr, LDD_I2C_ADDRTYPE_7BITS, RGB_ADDR);
	// set up the address of the first output register
	I2C_Buf[0] = (RGB_COMMAND_BIT | REG);
	RGB_I2C_SENT_FLAG = FALSE;
	RGB_Sensor_MasterSendBlock(DeviceDataPtr, I2C_Buf, 1, LDD_I2C_NO_SEND_STOP);
	// wait until the I2C sent callback function sets the sent flag
	while (!RGB_I2C_SENT_FLAG);


	I2C_Buf[0] = (value & 0xFF);
	RGB_I2C_SENT_FLAG = FALSE;
	RGB_Sensor_MasterSendBlock(DeviceDataPtr, I2C_Buf, 1, LDD_I2C_SEND_STOP);
	// wait until the I2C sent callback function sets the sent flag
	while (!RGB_I2C_SENT_FLAG);

	do
	{
		RGB_Sensor_CheckBus(DeviceDataPtr, &BusState);
	} while (BusState != LDD_I2C_IDLE);


	return;
}

uint16_t RGB_Read16(LDD_TDeviceData *DeviceDataPtr, uint8_t REG){
  uint16_t x;
  LDD_I2C_TBusState BusState;		// I2C bus state

  RGB_Sensor_SelectSlaveDevice(DeviceDataPtr, LDD_I2C_ADDRTYPE_7BITS, RGB_ADDR);

  // set up the address of the first output register
  I2C_Buf[0] = (RGB_COMMAND_BIT | REG);
  RGB_I2C_SENT_FLAG = FALSE;
  RGB_Sensor_MasterSendBlock(DeviceDataPtr, I2C_Buf, 1, LDD_I2C_NO_SEND_STOP);
  // wait until the I2C sent callback function sets the sent flag
  while (!RGB_I2C_SENT_FLAG);

  // read the 6 bytes of sequential sensor data
  RGB_I2C_RCVD_FLAG = FALSE;
  RGB_Sensor_MasterReceiveBlock(DeviceDataPtr, I2C_Buf, 2, LDD_I2C_SEND_STOP);
  // wait until the I2C received callback function sets the received flag
  while (!RGB_I2C_RCVD_FLAG);
  // wait until the I2C bus is idle

  do
  	{
  		RGB_Sensor_CheckBus(DeviceDataPtr, &BusState);
  	} while (BusState != LDD_I2C_IDLE);

  x = I2C_Buf[1]*256+I2C_Buf[0];
  return x;
}

void RGB_Enable(void)
{
  RGB_Write8(RGB_Sensor_DeviceData, TCS34725_ENABLE, TCS34725_ENABLE_PON);
  for(int i=0;i<4;i++);
  RGB_Write8(RGB_Sensor_DeviceData, TCS34725_ENABLE, TCS34725_ENABLE_PON | TCS34725_ENABLE_AEN);
}
void RGB_Disable(void){
  uint8_t reg = 0;
  reg = RGB_Read8(RGB_Sensor_DeviceData,TCS34725_ENABLE);
  RGB_Write8(RGB_Sensor_DeviceData,TCS34725_ENABLE, reg & ~(TCS34725_ENABLE_PON | TCS34725_ENABLE_AEN));
}
void RGB_Init(void)
{
  RGB_Write8(RGB_Sensor_DeviceData,TCS34725_ATIME, 0xEB);
  RGB_Write8(RGB_Sensor_DeviceData,TCS34725_CONFIG, 0x00);
  RGB_Write8(RGB_Sensor_DeviceData,TCS34725_CONTROL, 0x01);
}
