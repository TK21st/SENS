/* ###################################################################
**     Filename    : main.c
**     Project     : SENS ver1
**     Processor   : MKL46Z256VLL4
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2015-07-08, 09:31, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.01
** @brief
**         Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup main_module main module documentation
**  @{
*/         
/* MODULE main */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "I2CFreedom.h"
#include "RGB_Sensor.h"
#include "USB.h"
#include "RGB_Sensor.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* User includes (#include below this line is not maintained by Processor Expert) */
#include "build.h"
#include "MMA.h"
#include "TCS_RGB.h"

//function prototype

void RGB_Run(void);
void Message_Gen(void);

// sensor data structures and state vectors
struct AccelSensor thisAccel;					// this accelerometer
struct RGBSensor thisRGB;

#define message_length  (12) // 6 values * 2 bytes/value
uint8_t message[message_length + 2]; //total length is values + flag

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */
  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/
  /* Write your code here */
  /* For example: for(;;) { } */
  RGB_Init();
  RGB_Enable();
  uint8_t ID_CHECK = RGB_Read8(RGB_Sensor_DeviceData,TCS34725_ID);
  if (ID_CHECK != 0x44){
   return FALSE;
  }

  MMA8451_Freedom_Init_50Hz(I2CFreedom_DeviceData, &thisAccel);

   /* F_READ: Fast read mode, data format limited to single byte (auto increment counter will skip LSB)
    * ACTIVE: Full scale selection
    */
  USB_UART_FLAG = TRUE;
   for(;;){
	   if(USB_UART_FLAG){
		   MMA8451_Freedom_ReadData(I2CFreedom_DeviceData, &thisAccel);
		   // scale the HAL-aligned accelerometer measurements
		   thisAccel.fGp[X] = (float) thisAccel.iGp[X] * thisAccel.fgPerCount;
		   thisAccel.fGp[Y] = (float) thisAccel.iGp[Y] * thisAccel.fgPerCount;
		   thisAccel.fGp[Z] = (float) thisAccel.iGp[Z] * thisAccel.fgPerCount;

		   RGB_Run();
		   Message_Gen();
		   USB_UART_FLAG = FALSE;
		   USB_SendBlock(USB_DeviceData, (byte *)message, 14);
	   }
   }
  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/


void Message_Gen(void){

	message[0] = 'A';
	message[1] = 'B';
	message[2] = thisRGB.RED[0];
	message[3] = thisRGB.RED[1];
	message[4] = thisRGB.GREEN[0];
	message[5] = thisRGB.GREEN[1];
	message[6] = thisRGB.BLUE[0];
	message[7] = thisRGB.BLUE[1];
	message[8] = (thisAccel.iGp[X] & 0xFF );
	message[9] = (thisAccel.iGp[X] >> 8);
	message[10] = (thisAccel.iGp[Y] & 0xFF );
	message[11] = (thisAccel.iGp[Y] >> 8);
	message[12] = (thisAccel.iGp[Z] & 0xFF );
	message[13] = (thisAccel.iGp[Z] >> 8);
}


void RGB_Run(void){
	RGB_Init();
	RGB_Enable();
	thisRGB.CLEAR[0] = RGB_Read8(RGB_Sensor_DeviceData, CLEAR_L);
	thisRGB.CLEAR[1] = RGB_Read8(RGB_Sensor_DeviceData, CLEAR_H);
	thisRGB.RED[0] = RGB_Read8(RGB_Sensor_DeviceData, RED_L);
	thisRGB.RED[1] = RGB_Read8(RGB_Sensor_DeviceData, RED_H);
	thisRGB.BLUE[0] = RGB_Read8(RGB_Sensor_DeviceData, BLUE_L);
	thisRGB.BLUE[1] = RGB_Read8(RGB_Sensor_DeviceData, BLUE_H);
	thisRGB.GREEN[0] = RGB_Read8(RGB_Sensor_DeviceData, GREEN_L);
	thisRGB.GREEN[1] = RGB_Read8(RGB_Sensor_DeviceData, GREEN_H);

	for(int j = 0; j<500; j++); //delay for integration time (dependent on integration time)
	thisRGB.clear = thisRGB.CLEAR[1]*256+thisRGB.CLEAR[0];
	thisRGB.red = thisRGB.RED[1]*256+thisRGB.RED[0];
	thisRGB.green = thisRGB.GREEN[1]*256+thisRGB.GREEN[0];
	thisRGB.blue = thisRGB.BLUE[1]*256+thisRGB.BLUE[0];
	//RGB_Disable();
}
