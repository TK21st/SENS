/*
 * build.h
 *
 *  Created on: Oct 3, 2015
 *      Author: Tingkai
 */

#ifndef SOURCES_BUILD_H_
#define SOURCES_BUILD_H_

/* easier for XYZ Data Storage */
#define true 1
#define false 0
#define X 0
#define Y 1
#define Z 2

#define I2C_BUF_LEN		16

// Freedom FRDM-KL46Z board sensor I2C addresses
#define MMA8451_FRDM_I2C_ADDR		0x1D

// MMA8451 registers and constants
#define MMA8451_STATUS					0x00
#define MMA8451_OUT_X_MSB       	  	0x01
#define MMA8451_WHO_AM_I      			0x0D
#define MMA8451_XYZ_DATA_CFG     	  	0x0E
#define MMA8451_CTRL_REG1        	 	0x2A
#define MMA8451_CTRL_REG2         		0x2B
#define MMA8451_WHO_AM_I_VALUE     		0x1A



#define TCS34725_ENABLE			(0x00)
#define TCS34725_ENABLE_PON 	(0x01)
#define TCS34725_ENABLE_AEN		(0x02)
#define TCS34725_ENABLE_AIEN	(0x10)
#define TCS34725_ENABLE_WEN		(0x08)
#define TCS34725_ID				(0x12)

#define TCS34725_ATIME			(0x01)
#define TCS34725_WTIME			(0x03)
#define TCS34725_CONFIG			(0x0D)
#define TCS34725_CONTROL		(0x0F)

#define CLEAR_L		(0x14)
#define CLEAR_H		(0x15)
#define RED_H		(0x17)
#define RED_L		(0x16)
#define BLUE_H		(0x1B)
#define BLUE_L		(0x1A)
#define GREEN_H		(0x19)
#define GREEN_L		(0x18)

#define RGB_ADDR	(0x29) // Sensor Slave Address

#define RGB_COMMAND_BIT (0xa0)

bool RGB_I2C_SENT_FLAG;
bool RGB_I2C_RCVD_FLAG;
bool MMA_I2C_SENT_FLAG;
bool MMA_I2C_RCVD_FLAG;
bool USB_UART_FLAG;


struct RGBSensor{
	int clear,red,green,blue;
	uint8_t CLEAR[2],RED[2],GREEN[2],BLUE[2];
};


struct AccelSensor
{
	int16 iGp[3];			// 25Hz integer readings (counts)
	float fGp[3];			// 25Hz readings (g)
	float fgPerCount;		// initialized to FGPERCOUNT
};


#endif /* SOURCES_BUILD_H_ */
